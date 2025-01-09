@echo off

echo [INFO] Cleaning up...

wsl -d kali-linux rm -f *.o *.bin
wsl -d kali-linux rm -f kernel/arch/i386/*.o
wsl -d kali-linux rm -f *.iso

echo [INFO] Done!