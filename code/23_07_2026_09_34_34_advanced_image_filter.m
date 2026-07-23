% Image Filter
% Advanced-level implementation using convolutional algorithms and MATLAB's built-in functions.

classdef ImageFilter < handle
    properties
        image
        filter
    end
    
    methods
        function obj = ImageFilter(imagePath, filterType)
            % Load the image file
            obj.image = imread(imagePath);
            
            % Determine the filter based on the type
            switch filterType
                case 'blur'
                    obj.filter = fspecial('average');
                case 'sharpen'
                    obj.filter = fspecial('laplacian');
                case 'emboss'
                    obj.filter = fspecial('emboss');
                otherwise
                    error('Invalid filter type. Choose from ''blur'', ''sharpen'', or ''emboss''.');
            end
        end
        
        function filteredImage = applyFilter(obj)
            % Convolve the image with the filter to apply the desired effect
            filteredImage = imfilter(obj.image, obj.filter, 'replicate');
        end
    end
end

% Test the Image Filter class
if nargin == 0
    imagePath = 'path_to_your_image.jpg';  % Replace with your image path
    filterType = 'blur';  % Choose from ''blur'', ''sharpen'', or ''emboss''
    
    % Create an instance of the ImageFilter class
    obj = ImageFilter(imagePath, filterType);
    
    % Apply the filter and display the result
    filteredImage = obj.applyFilter();
    imshow(filteredImage);
else
    % Call the main function if image path and filter type are provided as arguments
    imgFilter(obj);
end

function imgFilter(obj)
    % Apply the filter and display the result
    filteredImage = obj.applyFilter();
    imshow(filteredImage);
end