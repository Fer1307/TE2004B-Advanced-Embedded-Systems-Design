clc;
clear;

disp("Cámaras detectadas:");
webcamlist

cam = webcam(2);

preview(cam);