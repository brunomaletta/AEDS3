a = read.csv("times.txt")
pdf("grafico.pdf")
plot(a, xlab="Vertices", ylab="Tempo (s)")
dev.off()
