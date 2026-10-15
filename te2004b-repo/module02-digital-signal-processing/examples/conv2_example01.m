% Se lee la imagen
originalImage = imread("mandril_gray.tif");

% Se convierte a escala de grises
%originalImage2 = im2gray(originalImage);

% Se convierte de uint8 a double
imgDouble = double(originalImage);

% Kernel promediador 9x9
kernel = [-1 -2 -1;
           0  0  0;
           1  2  1];

% Convolución
blurredImage = conv2(imgDouble, kernel, "same");

% Mostrar original y resultado
imshowpair(originalImage, blurredImage, "montage")