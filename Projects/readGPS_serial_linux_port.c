#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define SERIAL_PORT "/dev/tty10"
#define BUFFER_SIZE 1024

int main() {
    int serialPort;
    char buffer[BUFFER_SIZE];
    int bytesRead;
    struct termios readGPS;

    // Opening the serial port
    serialPort = open(SERIAL_PORT, O_RDONLY | O_NOCTTY | O_NDELAY);
    if (serialPort < 0) {
        fprintf(stderr, "Error opening serial port\n");
        return 1;
    }

    // Setting the serial port options
    tcgetattr(serialPort, &readGPS); //retrieving the current attributes of the serial port specified by serialPort
    cfsetispeed(&readGPS, B9600); //setting the input baud rate of the serial port to 9600 baud
    cfsetospeed(&readGPS, B9600); //setting the output baud rate of the serial port to 9600 baud
    readGPS.c_cflag &= ~PARENB; //disabling parity check
    readGPS.c_cflag &= ~CSTOPB; //setting the number of stop bits to 1
    readGPS.c_cflag &= ~CSIZE; //clearing the bits that determine the number of data bits
    readGPS.c_cflag |= CS8; //setting the number of data bits to 8
    readGPS.c_cflag &= ~CRTSCTS; //disabling the hardware flow control (RTS/CTS)
    readGPS.c_cflag |= CREAD | CLOCAL; //enableing both receiving characters and ignoring modem control lines
    readGPS.c_iflag &= ~(IXON | IXOFF | IXANY); //disabling software flow control (XON/XOFF)
    readGPS.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); //disabling canonical input mode, echoing of input characters, and signal generation
    readGPS.c_oflag &= ~OPOST; //disabling output processing
    readGPS.c_cc[VMIN] = 1; //setting the minimum number of characters to read at a time to 1
    readGPS.c_cc[VTIME] = 0; //setting the time to wait for input in tenths of a second to 0
    tcsetattr(serialPort, TCSANOW, &readGPS); //setting the attributes of the serial port specified by serialPort to the values in readGPS. The TCSANOW parameter specifies that the change should take effect immediately

    // Reading data from the serial port
    while (1) {
        bytesRead = read(serialPort, buffer, BUFFER_SIZE);
        if (bytesRead > 0) {
            printf("Received %d bytes: %.*s\n", bytesRead, bytesRead, buffer);
        }
        else if (bytesRead < 0) {
            fprintf(stderr, "Error reading serial data\n");
            break;
        }
    }

    // Closing the serial port
    close(serialPort);
    return 0;
}