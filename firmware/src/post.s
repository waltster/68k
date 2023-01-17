| Copyright 2022, Walter Pach. All rights reserved

.section .text

| 'start' is the first piece of code to run after initialization. Ideally it 
| will stabilize any hardware before jumping to a user-defined program.
.global start
start:
    
