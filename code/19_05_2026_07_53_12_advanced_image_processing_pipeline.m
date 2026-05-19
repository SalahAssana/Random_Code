% Image Processing Pipeline
classdef ImageProcessingPipeline
    methods
        function obj = ImageProcessingPipeline(image)
            % Initialize image processing pipeline with input image
            obj.image = image;
        end
        
        function filteredImage = filterImage(obj, filterType)
            % Apply filters to the input image based on filter type
            switch filterType
                case 'blur'
                    filteredImage = imfilter(obj.image, fspecial('average', 5));
                case 'sharpen'
                    kernel = [0 -1 0; -1 5 -1; 0 -1 0];
                    filteredImage = imfilter(obj.image, kernel);
                otherwise
                    error('Invalid filter type');
            end
        end
        
        function resizedImage = resizeImage(obj, newWidth, newHeight)
            % Resize the input image to a specified width and height
            resizedImage = imresize(obj.image, [newHeight newWidth]);
        end
        
        function features = extractFeatures(obj, featureType)
            % Extract features from the processed image based on feature type
            switch featureType
                case 'histogram'
                    features = rgbhist(obj.image);
                case 'texture'
                    textureFeatures = graycomarr(obj.image, [0 1; 1 0]);
                    features = cat(3, obj.image, textureFeatures);
                otherwise
                    error('Invalid feature type');
            end
        end
    end
    
    methods (Static)
        function image = loadSyntheticImage()
            % Load a synthetic RGB image for testing purposes
            image = imread('synthetic_image.png');
        end
    end
end

% Main script to test the Image Processing Pipeline
if true
    % Load synthetic RGB image
    image = ImageProcessingPipeline.loadSyntheticImage();
    
    % Create an instance of the pipeline and apply filters
    pipeline = ImageProcessingPipeline(image);
    filteredBlur = pipeline.filterImage('blur');
    filteredSharpen = pipeline.filterImage('sharpen');
    
    % Resize the original image to a new size
    resizedImage = pipeline.resizeImage(200, 100);
    
    % Extract features from the processed images
    histogramFeaturesBlur = pipeline.extractFeatures('histogram', filteredBlur);
    textureFeaturesSharpen = pipeline.extractFeatures('texture', filteredSharpen);
end