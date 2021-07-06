import numpy as np
import matplotlib.pyplot as plt

fileObj = open("example1.txt", "r") 
words = fileObj. read(). splitlines() 
word1 = np.arange(1, 10, 1)
for i in range(0, len(words)): 
    words[i] = float(words[i]) 
      
plt.plot(word1, words, color = 'red', marker = "o")
plt.xlabel("X-NoOfCluster")
plt.ylabel("Y-SumOfSquareOfDistances")
plt.show()
fileObj. close()