import subprocess
hs = subprocess.check_output(["hostname"])[:-1]
cpuid = subprocess.check_output("cat /proc/cpuinfo | grep processor | wc -l", shell=True)[:-1]
print("Hello world from " +  hs + " CPU " + cpuid)