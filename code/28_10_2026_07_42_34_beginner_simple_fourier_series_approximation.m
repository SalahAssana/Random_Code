% Simple Fourier Series Approximation in MATLAB

% Load required libraries
library('fourier');

% Define sample signal (synthetic data)
t = 0:0.01:1; % time array
x = sin(2*pi*10*t) + 0.5*sin(2*pi*20*t); % signal with two frequencies

% Plot the original signal
figure;
plot(t,x);
xlabel('Time (s)');
ylabel('Amplitude');
title('Original Signal');

% Perform Fourier Transform
X = fft(x);

% Calculate frequency array
f = (1/length(t))*[0:length(t)/2-1,length(t)/2:length(t)];

% Plot the magnitude of the FFT
figure;
plot(f,abs(X));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('FFT Magnitude');

% Approximate the original signal using Fourier series
n = 20; % number of harmonics
A = X(1:n+1); % amplitude array
P = f(1:n+1); % frequency array

x_approx = sum(A.*cos(2*pi*P.*t),2);

% Plot the approximate signal
figure;
plot(t,x_approx);
xlabel('Time (s)');
ylabel('Amplitude');
title('Approximated Signal');

% Compare original and approximated signals
figure;
plot(t,[x;x_approx]);
xlabel('Time (s)');
ylabel('Amplitude');
legend('Original', 'Approximated');
title('Comparison of Original and Approximated Signals');