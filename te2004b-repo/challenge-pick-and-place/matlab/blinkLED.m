function blinkLED()%#codegen
% Create a Raspberry Pi object
r = raspi('<IP_RASPBERRY_PI>', '<usuario>', '<contrasena>');
%se obtiene el led disponible en la tarjeta
led = r.AvailableLEDs{1};
% Blink the LED for 100 cycles
for count = 1:20
    % Turn on the LED
    writeLED(r,led, 1);
    % Pause for 0.5 seconds
    pause(0.5);
    % Turn off the LED
    writeLED(r,led, 0);
    % Pause for 0.5 seconds
    pause(0.5);
end
%se prepara el hardware en el prompt de matlab
% >>board = targetHardware('Raspberry Pi (64bit)')
%se crea un ejecutable y se ejecuta como standalone en la RPI
% >>deploy(board,'blinkLED')