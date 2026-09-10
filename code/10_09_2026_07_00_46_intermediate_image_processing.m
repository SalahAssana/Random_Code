% Define filter kernels for blur, sharpen, and thresholding
blurKernel = [0.0625 0.125 0.0625; 
              0.125 0.25 0.125;
              0.0625 0.125 0.0625];

sharpenKernel = [-1 -1 -1; -1 5 -1; -1 -1 -1];

thresholdKernel = [0 0 0; 
                   0 1 0; 
                   0 0 0];

% Load sample image
image = imread('sample_image.jpg');

% Convert to grayscale for simplicity
grayImage = rgb2gray(image);

% Define function to apply filter using convolution
function filteredImage = applyFilter(filterKernel, inputImage)
    [height, width] = size(inputImage);
    
    % Pad the filter kernel to match the image size
    paddedKernel = padarray(filterKernel, [size(filterKernel, 1) - 2 0], 'symmetric');
    
    % Initialize output array
    filteredImage = zeros(height, width);
    
    for i = 1:height
        for j = 1,width
            % Convolve the filter kernel with the input image
            sum = 0;
            for k = 1:size(paddedKernel, 1)
                for l = 1,size(paddedKernel, 2)
                    sum = sum + paddedKernel(k,l) * inputImage(i+k-1,j+l-1);
                end
            end
            
            % Add the filtered value to the output array
            filteredImage(i,j) = sum;
        end
    end
end

% Apply blur filter
blurredImage = applyFilter(blurKernel, grayImage);

% Display blurred image
figure; imshow(blurredImage); title('Blurred Image');

% Apply sharpen filter
sharpenedImage = applyFilter(sharpenKernel, grayImage);

% Display sharpened image
figure; imshow(sharpenedImage); title('Sharpened Image');

% Apply thresholding filter (convert to binary)
thresholdedImage = thresholdImage = applyFilter(thresholdKernel > 0.5, grayImage);
thresholdedImage = thresholdedImage > 127;

% Display thresholded image
figure; imshow((thresholdedImage + 1) * 255); title('Thresholded Image');