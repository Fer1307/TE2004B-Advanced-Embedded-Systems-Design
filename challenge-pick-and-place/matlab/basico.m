%primeros pasos con la RPi
clear
r = raspi('<IP_RASPBERRY_PI>', '<usuario>', '<contrasena>');
%se obtiene el led disponible en la tarjeta
led = r.AvailableLEDs{1};
%se actua sobre el led
for i = 1:10
    writeLED(r, led, 0);
    pause(0.5);
    writeLED(r, led, 1);
    pause(0.5);
end
% se regresa al led al estado original
%system(r, 'echo "mmc0" | sudo tee /sys/class/leds/led0/trigger');
%system(r, 'echo "mmc0" | sudo tee /sys/class/leds/ACT/trigger'); %más
%reciente versión