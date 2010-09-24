install.packages("signal")
library('signal')
f1 = remez(128, c(0,200/44100,400/44100,1), c(1,1,0,0))
save(f1, file = "~/routput.txt", ascii = TRUE)+