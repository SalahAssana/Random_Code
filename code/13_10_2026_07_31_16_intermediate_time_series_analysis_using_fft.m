% Time Series Analysis using FFT
%
% This script demonstrates how to apply Fast Fourier Transform (FFT) to analyze 
% and visualize time series data, identifying patterns and trends.

function time_series_analysis()
    % Load synthetic time series data
    t = 0:0.1:10;  % time values
    x = sin(2*pi*2*t) + 0.5*sin(4*pi*3*t);  % synthetic signal with two frequencies

    % Perform FFT on the time series data
    X = fft(x);

    % Calculate the frequency axis
    f = (1/(10/length(t)))*[0:length(t)/2-1]; 

    % Plot the original time series and its FFT magnitude spectrum
    figure;
    subplot(2,1,1);
    plot(t,x,'b');
    title('Original Time Series');
    xlabel('Time (s)');
    ylabel('Amplitude');

    subplot(2,1,2);
    plot(f,abs(X));
    title('FFT Magnitude Spectrum');
    xlabel('Frequency (Hz)');
    ylabel('Magnitude';

    % Calculate the power spectral density (PSD)
    PSD = abs(X).^2 ./ length(t);

    % Plot the PSD
    figure;
    plot(f,PSD);
    title('Power Spectral Density');
    xlabel('Frequency (Hz)');
    ylabel('PSD (Hz)');

end

time_series_analysis()