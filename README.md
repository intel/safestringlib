# safestringlib
The Secure Development Lifecycle (SDL) recommends banning certain C Library functions because they directly contribute 
to security vulnerabilities such as buffer overflows. However routines for the manipulation of strings and memory buffers 
are common in software and firmware, and are essential to accomplish certain programming tasks. Safer replacements for 
these functions that avoid or prevent serious security vulnerabilities (e.g. buffer overflows, string format attacks, 
conversion overflows/underflows, etc.) are available in the SafeString Library. 

This library includes routines for safe string operations (like strcpy) and memory routines (like memcpy) that are 
recommended for Linux/Android operating systems, and will also work for Windows. This library is especially useful for 
cross-platform situations where one library for these routines is preferred. 

The Safe String Library is based on the Safe C Library by Cisco, and includes replacement C Library functions for the SDL 
banned functions, as well as a number of additional useful routines that are also susceptible to buffer overflows. This
library continues to be made available under the MIT Open Source License.

Cisco's Safe C Library was extended by Intel's Security Center of Excellence (SeCoE) to add additional routines, and 
include additional unit tests.

LIST OF PRIMARY FUNCTIONS:
-----------------------------
To be completed

LIST OF ADDITIONAL STRING ROUTINES:
------------------------------------
To be completed

PLANNED ENHANCEMENTS:
----------------------
- Add full sprintf_s() support
- Add full sscanf_s() support
