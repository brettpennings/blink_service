
require 'serialport'
sp = SerialPort.new "COM3", 9600
sleep 2.0

sp.write "blink 200\n"

# wait a second for the command to process before expecting a response
sleep 2.0

# we should get back an echo here (if everything is working)
puts sp.read

sleep 3.0

# puts sp.get_modem_params()

# sp.flush

# while 1 do
	# data = sp.getc
	# if data != '' then
		# puts data.ord
	# end
# end