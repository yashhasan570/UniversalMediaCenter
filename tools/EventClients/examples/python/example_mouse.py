#!/usr/bin/env python3

# This is a simple example showing how you can send mouse movement
# events to .

# NOTE: Read the comments in 'example_button1.py' for a more detailed
# explanation.

import os
from socket import *
import sys

if os.path.exists("../../lib/python"):
    # try loading modules from source directory
    sys.path.append("../../lib/python")

    from client import *

    ICON_PATH = "../../icons/"
else:
    # fallback to system wide modules

    from universalmediacenter.client import *
    from universalmediacenter.defs import *

def main():
    import time
    import sys

    host = "localhost"
    port = 9777
    addr = (host, port)

    sock = socket(AF_INET,SOCK_DGRAM)

    # First packet must be HELO and can contain an icon
    packet = PacketHELO("Example Mouse", ICON_PNG,
                        ICON_PATH + "/mouse.png")
    packet.send(sock, addr)

    # wait for notification window to close (in )
    time.sleep(2)

    # send mouse events to take cursor from top left to bottom right of the screen
    # here 0 to 65535 will map to 's screen width and height.
    # Specifying absolute mouse coordinates is unsupported currently.
    for i in range(0, 65535, 2):
        packet = PacketMOUSE(i,i)
        packet.send(sock, addr)

    # ok we're done, close the connection
    packet = PacketBYE()
    packet.send(sock, addr)

if __name__=="__main__":
    main()
