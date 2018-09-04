
library(readr)

queue1 <- read_csv("queue1.csv", col_names = c("element_count", "time", "throughput"))
queue2 <- read_csv("queue2.csv", col_names = c("element_count", "time", "throughput"))
queue3 <- read_csv("queue3.csv", col_names = c("element_count", "time", "throughput"))
queue4 <- read_csv("queue4.csv", col_names = c("element_count", "time", "throughput"))
queue5 <- read_csv("queue5.csv", col_names = c("element_count", "time", "throughput"))

plot_frame <- data.frame("queue1" = queue1$throughput, 
                         "queue2" = queue2$throughput,
                         "queue3" = queue3$throughput,
                         "queue4" = queue4$throughput,
                         "queue5" = queue5$throughput)

write_csv(plot_frame, "comparison_plot.csv", col_names = FALSE)

