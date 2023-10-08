#!/usr/bin/octave -qf

################################################################################
#
# Configuration
#
################################################################################
fSampling = 2^15;
nSamplesInLb = 9;
nSamples = 2^nSamplesInLb;
fNyquist = fSampling / 2;
fSpectrum = fSampling / nSamples;
nBands = 8;

printf("Sampling Frequency=%d Hz => Nyquist Frequency=%d Hz\n", fSampling, fNyquist);
printf("Number of Samples=%d => Spectrum Width=%d Hz\n", nSamples, fSpectrum);
printf("Number of Frequency Bands=%d\n\n", nBands);

t = 0:1:(nSamples-1);
frequencies = [ 28 55 110 220 440 880 1760 3520 7040 14080 ];
frequency = frequencies(5);

################################################################################
#
# Sample Data
#
################################################################################
blinkenlight_data;

################################################################################
#
# Functions
#
################################################################################
function factor = hanning(idx, len)
    p = idx * ((2 * pi) / (len - 1));
    factor = 0.5 * (1 - cos(p));
endfunction

function value = bandpass(samples, center, width)
    left = center - width;
    len = (2*width) + 1;

    factors = [0:len+1];
    factors(1) = 0;

    value = 0;
    for idx = [1:len]
        factor = hanning(idx, len+2);
        factors(1+idx) = factor;
        value += factor * samples(left + idx + 1);
    endfor

    factors(len+2) = 0;

    plot([0:len+1], factors);
endfunction

function value = hipass(samples, center, width)
    left = center - width;
    len = width;

    factors = [0:len+1];
    factors(1) = 0;

    value = 0;
    for idx = [1:len]
        factor = hanning(idx, (2*width)+3);
        factors(1+idx) = factor;
        value += factor * samples(left + idx);
    endfor

    factors(len+2) = 1;

    plot([0:len+1], factors);
endfunction

################################################################################
#
# Window Function
#
################################################################################
# Substract DC component of sampled data. This means the samples will be
# centered around 0 instead of 128
float_samples = (samples_1 - 128) / 128;

for idx = [1:nSamples]
    float_samples(idx) *= hanning(idx, nSamples);
endfor

################################################################################
#
# Actual FFT and Amplitude Calculation
#
################################################################################
fft_samples = fft(float_samples);

# Calculate the (squared) amplitudes of the samples [0:255] which is half of
# the full spectrum. This works because our input samples were all real
# values, so the upper half will be symmetric to the lower half.
fft_amplitudes = abs(fft_samples);
fft_amplitudes(:, ((nSamples/2)+1):nSamples) = [];

################################################################################
#
# Filter Bands
#
################################################################################
f = 0:1:nBands;
amplitudes = [0:nBands];

# Define initial vector. To be filled by the Filters below
for i = [1:9]
    amplitudes(i) = 0;
endfor

# Cut-off zeroth Band to strip DC components
printf("filter=%d n=%d w2=%d left=%d center=%d right=%d\n", -1, 1, 1, 0, 0, 0);
printf("\tCut-off Frequency=%d Hz\n", fSpectrum/2);

# Lowest filter is single-band only
printf("filter=%d n=%d w2=%d left=%d center=%d right=%d\n", 0, 1, 1, 1, 1, 1);
printf("\tCenter Frequency=%d Hz\n", fSpectrum);
amplitudes(1) = fft_amplitudes(2);

# (nBands - 1) Band Pass Filters
figure(2);
for filter = [1:nBands-1]
    center = 2^(filter)+1;

    w2 = 2^(filter-1);
    n = 2*w2 + 1; # (2^(filter))+1;
    left = center - w2;
    right = center + w2;

    printf("filter=%d n=%d w2=%d left=%d center=%d right=%d\n", filter, n, w2, left, center, right);
    frequency = (center - 1) * fSpectrum;
    printf("\tCenter Frequency=%d Hz\n", frequency);

    subplot(nBands / 2, 2, filter);
    amplitudes(filter + 1) = bandpass(fft_amplitudes, center, w2);
    title(sprintf("Window Function for Filter %d (Center=%d, W/2=%d)", filter, center, w2));
endfor

# High Pass Filter for upper half of spectrum. Keep in mind that only half of
# the spectrum/samples is usable since the input was all-real samples.
center = 2^nBands;
n = (nSamples/2)/2;
w2 = n;
left = center - w2;
right = center;

printf("filter=%d n=%d w2=%d left=%d center=%d right=%d\n", nBands, n, w2, left, center, right);
frequency = center * fSpectrum;
printf("\tHi-Pass Frequency=%d Hz\n", frequency);

subplot(nBands / 2, 2, nBands);
amplitudes(nBands + 1) = hipass(fft_amplitudes, center, w2);
title(sprintf("Window Function for Hi-Pass Filter %d (Center=%d, W/2=%d)", nBands, center, w2));

################################################################################
#
# Adjust for LED Bands
#
################################################################################
led_bands = [0:nBands];

factors = [ 1 1 1 1 1 1 1 1 1 ];
# Define initial vector. To be filled below
for i = [1:9]
    ratio = 16.0;
    factor = factors(i);
    led_bands(i) = (factor * amplitudes(i))/ratio;
endfor

################################################################################
#
# Plot frequency spectrum
#
################################################################################
figure(1);
subplot (4, 1, 1)
plot(t, float_samples, ':;float;');
subplot (4, 1, 2)
plot(t, fft_samples, ':;fft_samples;');
subplot (4, 1, 3)
plot(f, amplitudes, '-;amplitudes;');
subplot (4, 1, 4)
plot(f, led_bands, '-;LEDs;');

