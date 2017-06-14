SetupDatasets();
data = dataset(1);

aligned_ffh = [data.file '-aligned.ffh'];
intensity_file = [data.file '-aligned I raw.tif'];
tau_file = [data.file '-aligned tau_1 raw.tif'];
merged_file = [data.file '-aligned-intensity-normalised-merged.tif'];


r = FlimReaderMex(aligned_ffh);
intensity_normalisation = FlimReaderMex(r,'GetIntensityNormalisation');
FlimReaderMex(r,'Delete');
clear FlimReaderMex

intensity_normalisation = double(intensity_normalisation);
intensity_normalisation = intensity_normalisation / mean(intensity_normalisation(:));

intensity = imread(intensity_file);
tau = imread(tau_file);

intensity = intensity ./ intensity_normalisation;
imagesc(intensity);

merged = ShowFLIM(tau',intensity',data.tau_lim,data.I_lim,false);

figure(3)
imagesc(merged)

imwrite(merged,merged_file)