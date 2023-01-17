/* 
 *  Originally by https://github.com/TomNisbet/TommyPROM/tree/master/unlock-ben-eater-hardware
 *  Modified by Walter Pach
 *  
 *  Utility to unlock 28C256 Software Data Protection (SDP) for the Ben Eater EEPROM 
 *  programmer design.  This hardware is similar to the TommyPROM hardware, but it uses
 *  different shift register chips and different pin assignments.
 *  
 *  To meet the timing requirements of the SDP unlock, this code uses direct port writes
 *  to set and read values on the data bus.  It will work Arduino Uno and Nano hardware,
 *  but would require changes for other platforms.
 */
#define SHIFT_DATA 2
#define SHIFT_CLOCK 3
#define SHIFT_LATCH 4
#define WRITE_ENABLE A2
#define LED 13

#define EEPROM_SIZE 262144

// 32 byte test pattern to verify the EEPROM device.  The pattern includes a walking one
// and a walking zero, which may help to detect pins that are tied together or swapped.
byte data[] = {
    'A',  'B',  'C',  'D',  'E',  'F',  'G',  'H',
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
    0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe,
    0x00, 0xff, 0x55, 0xaa, 0xbb, 0xcc, 0xdd, 0xee,
};

void enableWrite() { 
  digitalWrite(WRITE_ENABLE, LOW);
}

void disableWrite() { 
  digitalWrite(WRITE_ENABLE, HIGH);
}

void testWrite() {
  // Program a test pattern and fill the remainder of the first block with 0xff
  Serial.print("Programming EEPROM...");
  for (word address = 0; (address < sizeof(data)); address++) {
    writeEEPROM(address, data[address]);
  }
    
 // for (word address = sizeof(data); (address < EEPROM_SIZE); address++) {
   // writeEEPROM(address, 0xFF);
  //}
}

void clearEEPROM() {
    disableWrite();
    setDataBusMode(OUTPUT);

    setByte(0xaa, 0x5555);
    setByte(0x55, 0x2aaa);
    setByte(0x80, 0x5555);
    setByte(0xaa, 0x5555);
    setByte(0x55, 0x2aaa);
    setByte(0x10, 0x5555);

    setDataBusMode(INPUT);
    delay(50); // Double the time required for the chip to finish erasing.
}

void setup() {
  pinMode(SHIFT_DATA, OUTPUT);
  pinMode(SHIFT_CLOCK, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);
  disableWrite();
  pinMode(WRITE_ENABLE, OUTPUT);
  Serial.begin(57600);

  Serial.println("\nReading EEPROM");
  printContents(128);

  Serial.print("\nDisabling EEPROM Software Data Protection(SDP)...");
  disableSoftwareWriteProtect();
  Serial.println(" done!");

  //Serial.print("Clearing EEPROM...");
  //clearEEPROM();
  //Serial.println(" done!");
  
  Serial.print("\nDoing test...");
  testWrite();  
  Serial.println(" done!");

  // Read and print out the contents of the EERPROM
  Serial.println("Reading EEPROM");
  printContents(128);
}

void loop() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED,HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}


// Output the address bits and outputEnable signal using shift registers.
void setAddress(int addr, bool outputEnable) {
  // Set the highest bit as the output enable bit (active low)
  if (outputEnable) {
    addr &= ~0x8000;
  } else {
    addr |= 0x8000;
  }
    
  byte dataMask = 0x04;
  byte clkMask = 0x08;
  byte latchMask = 0x10;

    // Make sure the clock is low to start.
    PORTD &= ~clkMask;

    // Shift 16 bits in, starting with the MSB.
    for (uint16_t ix = 0; (ix < 16); ix++)
    {
        // Set the data bit
        if (addr & 0x8000)
        {
            PORTD |= dataMask;
        }
        else
        {
            PORTD &= ~dataMask;
        }

        // Toggle the clock high then low
        PORTD |= clkMask;
        delayMicroseconds(3);
        PORTD &= ~clkMask;
        addr <<= 1;
    }

    // Latch the shift register contents into the output register.
    PORTD &= ~latchMask;
    delayMicroseconds(1);
    PORTD |= latchMask;
    delayMicroseconds(1);
    PORTD &= ~latchMask;
}



// Read a byte from the EEPROM at the specified address.
byte readEEPROM(int address) {
    setDataBusMode(INPUT);
    setAddress(address, /*outputEnable*/ true);
    return readDataBus();
}

// Write a byte to the EEPROM at the specified address.
void writeEEPROM(int address, byte data) {
    setAddress(address, /*outputEnable*/ false);
    setDataBusMode(OUTPUT);
    writeDataBus(data);
    enableWrite();
    delayMicroseconds(1);
    disableWrite();
    delay(10);
}

// Read the first EEPOM_SIZE byte block of the EEPROM and dump it to the serial monitor.
void printContents(int size) {
    for (int base = 0; (base < (size != 0 ? size : EEPROM_SIZE)); base += 16) {
        byte data[16];
        for (int offset = 0; offset <= 15; offset += 1) {
            data[offset] = readEEPROM(base + offset);
        }

        char buf[80];
        sprintf(buf, "%04x:  %02x %02x %02x %02x %02x %02x %02x %02x   %02x %02x %02x %02x %02x %02x %02x %02x",
            base, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7],
            data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
        Serial.println(buf);
    }
}

// Write the special six-byte code to turn off Software Data Protection.
void disableSoftwareWriteProtect() {
    disableWrite();
    setDataBusMode(OUTPUT);

    setByte(0xaa, 0x5555);
    setByte(0x55, 0x2aaa);
    setByte(0x80, 0x5555);
    setByte(0xaa, 0x5555);
    setByte(0x55, 0x2aaa);
    setByte(0x20, 0x5555);

    setDataBusMode(INPUT);
    delay(10);
}

// Write the special three-byte code to turn on Software Data Protection.
void enableSoftwareWriteProtect() {
    disableWrite();
    setDataBusMode(OUTPUT);

    setByte(0xaa, 0x5555);
    setByte(0x55, 0x2aaa);
    setByte(0xa0, 0x5555);

    setDataBusMode(INPUT);
    delay(10);
}

// Set the I/O state of the data bus.
// The 8 bits data bus are is on pins D5..D12.
void setDataBusMode(uint8_t mode) {
    // On the Uno and Nano, D5..D12 maps to the upper 3 bits of port D and the
    // lower 5 bits of port B.
    if (mode == OUTPUT) {
        DDRB |= 0x1f;
        DDRD |= 0xe0;
    } else {
        DDRB &= 0xe0;
        DDRD &= 0x1f;
    }
}

// Read a byte from the data bus.  The caller must set the bus to input_mode
// before calling this or no useful data will be returned.
byte readDataBus() {
    return (PINB << 3) | (PIND >> 5);
}

// Write a byte to the data bus.  The caller must set the bus to output_mode
// before calling this or no data will be written.
void writeDataBus(byte data) {
     PORTB = (PORTB & 0xe0) | (data >> 3);
     PORTD = (PORTD & 0x1f) | (data << 5);
}

// Set an address and data value and toggle the write control.  This is used
// to write control sequences, like the software write protect.  This is not a
// complete byte write function because it does not set the chip enable or the
// mode of the data bus.
void setByte(byte value, word address) {
    setAddress(address, false);
    writeDataBus(value);

    delayMicroseconds(1);
    enableWrite();
    delayMicroseconds(1);
    disableWrite();
}
