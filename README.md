# sample_drivers_code
## Some Sample Codes of Windows Drivers 

### Develop and test enviornment:
* Develop: Windows10 1809, VisualStudio 2017, SDK: 10.0.17763.0, WDK 10
* Test: Windows10 1511



### Note before compile:
* Properties -> Configuration Properties -> C/C++ -> General -> Warning Level: Level1 (/W1)
* Properties -> Configuration Properties -> Linker -> General -> Treat Linker Warning As Errors: No (/WX:NO)
* Properties -> Configuration Properties -> Linker -> Command Line -> Additional Options: /INTEGRITYCHECK 
* Properties -> Configuration Properties -> Driver Settings -> General -> Target OS Version: Windows 10 or higher
* Properties -> Configuration Properties -> Inf2Cat -> General -> Use Local Time: Yes (/uselocaltime)


### List of sample codes:
* [MyPsSetCreateProcessNotifyRoutineEx](https://github.com/7eRoM/sample_drivers_code/blob/master/MyPsSetCreateProcessNotifyRoutineEx.c): PsSetCreateProcessNotifyRoutineEx
* [MyPsSetCreateProcessNotifyRoutineEx2](https://github.com/7eRoM/sample_drivers_code/blob/master/MyPsSetCreateProcessNotifyRoutineEx2.c): PsSetCreateProcessNotifyRoutineEx2
