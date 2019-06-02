import numpy as np
import math
import matplotlib.pyplot as plt
import re

topk = 19
botk = 6
nums = [6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]

basefile = "5"
numtrials = 10
baseno = 0
basea = 0
for t in range(numtrials):
	with open("test" + str(t)+basefile+".txt") as f:
	    content = f.readlines()

	content = [x.strip() for x in content]

	j = re.findall('\d+', content[11])
	baseno += int(j[0])
	m = re.findall('\d+', content[8])
	basea += int(m[0])

baseno = baseno/numtrials
basea = basea/numtrials

print(baseno)
print(basea)
quit()
numops = np.zeros(topk-botk+1)
numalt = np.zeros(topk-botk+1)

for t in range(numtrials):
	for k in range(6, topk+1):
		with open("test" + str(t)+str(k)+".txt") as f:
			content = f.readlines()

		content = [x.strip() for x in content]
		j = re.findall('\d+', content[11])
		numops[k-6] = (int(j[0])/baseno)
		m = re.findall('\d+', content[8])
		numalt[k-6] = (int(m[0])/basea)

numops = numops/numtrials
numalt = numalt/numtrials
print(numops)
print(numalt)

ratio = numops/numalt

plt.plot(nums, ratio)
plt.show()