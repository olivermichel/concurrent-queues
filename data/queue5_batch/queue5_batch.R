
library(readr)
queue5_batch <- read_csv("queue5_batch.csv", col_names = c("batch_size", "element_count", "time", "throughput"))
batch_size_throughput = aggregate(throughput ~ batch_size, queue5_batch, mean)
#plot(batch_size_throughput[,1], batch_size_throughput[,2], type="b", xlab = "batch size", ylab = "throughput [M elements/s]")
write_csv(batch_size_throughput, "batch_size_throughput_plot.csv", col_names = FALSE)