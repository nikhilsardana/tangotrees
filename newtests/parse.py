import numpy as np
import math
import matplotlib.pyplot as plt
import re

topk = 22
botk = 6
nums = [6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22]

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

baseno = baseno
basea = basea

numops = np.zeros(topk-botk+1)
numalt = np.zeros(topk-botk+1)

for t in range(numtrials):
	for k in range(6, 21):
		with open("test" + str(t)+str(k)+".txt") as f:
			content = f.readlines()

		content = [x.strip() for x in content]
		j = re.findall('\d+', content[11])
		numops[k-6] += (int(j[0])/baseno)
		m = re.findall('\d+', content[8])
		numalt[k-6] += (int(m[0])/basea)

numops[21-6] = 237916399/baseno
numalt[21-6] = 159911639/basea

numops[22-6] = 500239289/baseno
numalt[22-6] = 336618931/basea

print(numops)
print(numalt)

ratios = numalt/numops
print(ratios)

nums = np.asarray(nums)

# fit = np.log(np.log(nums-4))/14 + 0.968
fit = np.log(np.log(nums-4.1))/15 + 0.974

plt.plot(nums, ratios)
plt.plot(nums, fit)
plt.show()