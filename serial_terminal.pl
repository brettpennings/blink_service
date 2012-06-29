use strict;
use Win32::SerialPort qw( :STAT 0.19 );

# serial port setup
my $PortObj = new Win32::SerialPort ('COM9', 1)
       || die "Can't open COM9: $^E\n";    # $quiet is optional

# $PortObj->baudrate(9600);
$PortObj->baudrate(115200);
$PortObj->databits(8);
$PortObj->stopbits(1);
$PortObj->parity('none');
$PortObj->handshake('none');
$PortObj->buffers(4096, 4096);

$PortObj->write_settings || undef $PortObj;
$PortObj->save("ser.cfg");
$PortObj->close || die "failed to close";

$PortObj = tie (*FH, 'Win32::SerialPort', "ser.cfg") || die;
$| = 1;

while (1) {
	# send line
	# my $input = <>;
	# print FH $input;
	
	# get line
	while (my $output = getc FH) {
		print $output;
		# print ord($output);
		
		# print ($output & 0x8000) >> 15;
		# print ($output & 0x4000) >> 14;
		# print ($output & 0x2000) >> 13;
		# print ($output & 0x1000) >> 12;
		# print ($output & 0x0800) >> 11;
		# print ($output & 0x0400) >> 10;
		# print ($output & 0x0200) >> 9;
		# print ($output & 0x0100) >> 8;
		# print ($output & 0x80) >> 7;
		# print ($output & 0x40) >> 6;
		# print ($output & 0x20) >> 5;
		# print ($output & 0x10) >> 4;
		# print ($output & 0x08) >> 3;
		# print ($output & 0x04) >> 2;
		# print ($output & 0x02) >> 1;
		# print ($output & 0x01);
		print '|';
	}
}












