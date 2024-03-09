#!/usr/bin/python
import socket
import re

def get_processor_name():
    file = open("/proc/cpuinfo")
    for line in file:
        if "model name" in line:
            return re.sub(".*model name.*:", "", line, 1)
    return ""


hostname = socket.gethostname()

cpuid = get_processor_name()
print("Hello World from " + hostname + " CPU #" + cpuid)
