[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/OHwIpFF9)
# Project 1
Answer these questions please:

Project Overview:
-----------------------------------
What is the project about? Provide a brief overview that includes the project's name, purpose, and target audience.

This project mimics the debian bash terminal that on the users computer

Solution Approach:
------------------------------------------------------------

How did you approach the problem? Outline the steps or phases in your project development process?
I started with breaking down what functions i needed to do first, I decided to first start with the get user command function. With each function i looked up what the suggested functions in the comments did to get a better idea on how to implement them. After I completed part 2 of the project, that was when i first started to use valgrind to check for memory leaks and fix the leaks that did happen. After completing part 3 I added error handling.

Challenges and Solutions?
---------------------------
What challenges did you encounter while completeing your project, and how did you overcome them?
the parse command function was most challenging function to implement for me until i learned about strok() function in office hours which kind of works like .strip() in python


LLM Disclosure
--------------
Are there any external resources or references that might be helpful?


Testing and Validation
-----------------------
Testing Methodology: How did you test your project? Discuss any unit tests, integration tests, or user acceptance testing conducted.
Are there any specific commands or scripts that should be known?
My testing methodology was basically just entering any command i could think of and seeing the output and comparing it to the output of the actual shell

Example session
---------------
Provide examples on running your project

jasonappiah@debian:~/project1-JasonAK19$ ./test
>> history
176: history
177: exit
178: /proc/cpuinfo
179: exit
180: ls
181: cd
182: cd
183: pwd
184: exit
185: history
>> ls
main_template.c  Makefile  README.md  shelldir  simple_shell.c  test  testdir  utils.c  utils.h
>> pwd
/home/jasonappiah/project1-JasonAK19
>> /proc/cpuinfo
processor       : 0
vendor_id       : GenuineIntel
cpu family      : 6
model           : 191
model name      : 13th Gen Intel(R) Core(TM) i7-13700HX
stepping        : 2
microcode       : 0xffffffff
cpu MHz         : 2304.000
cache size      : 30720 KB
physical id     : 0
siblings        : 1
core id         : 0
cpu cores       : 1
apicid          : 0
initial apicid  : 0
fpu             : yes
fpu_exception   : yes
cpuid level     : 22
wp              : yes
flags           : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ht syscall nx rdtscp lm constant_tsc rep_good nopl xtopology nonstop_tsc cpuid tsc_known_freq pni pclmulqdq ssse3 cx16 pcid sse4_1 sse4_2 movbe popcnt aes rdrand hypervisor lahf_lm abm 3dnowprefetch invpcid_single ibrs_enhanced fsgsbase bmi1 bmi2 invpcid rdseed clflushopt arat md_clear flush_l1d arch_capabilities
bugs            : spectre_v1 spectre_v2 spec_store_bypass swapgs retbleed eibrs_pbrsb
bogomips        : 4608.00
clflush size    : 64
cache_alignment : 64
address sizes   : 39 bits physical, 48 bits virtual
power management:

>> exit

jasonappiah@debian:~/project1-JasonAK19$ ./test
>> ls
main_template.c  Makefile  README.md  shelldir  simple_shell.c  test  testdir  utils.c  utils.h
>> 
>> pwd
/home/jasonappiah/project1-JasonAK19
>> sdsadadasdsad
execution error: No such file or directory
>> cd testdir
>> cd ..
>>  
>>      
>> history
188: /proc/cpuinfo
189: exit
190: ls
191: 
192: pwd
193: sdsadadasdsad
194: cd
195:  
196:      
197: history
>> exit
