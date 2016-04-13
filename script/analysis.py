import os

def isFloat(value):
	try:
		float(value)
		return True
	except ValueError:	
		return False

csv_files = []
log_files = []
names = []
out_file = open("output.csv", "w")
time_slice = 0.0002

path = "../log_test/"

for root, dirs, files in os.walk(path):
	
	for f in files:
		if "swp" in f:
			continue
		elif "csv" in f:
			name = f.split(".")[0]
			names.append(name)
			csv_files.append(path+f)
		elif "log" in f:
			log_files.append(path+f)
		else:
			continue

names.sort()
csv_files.sort()
log_files.sort()

out_file.write("algorithm, key, mode, num of test, plaintext bytes, title, time(us), avg power(mW), max power(mW), min power(mW)\n");

# times[0]: Before encryption, times[1]: After encryption,
# times[2]: Before decryption, times[3]: After decryption
for n in range(len(csv_files)):
	f = open(csv_files[n], "r")
	g = open(log_files[n], "r")
	
	time_point = []

	s = ((csv_files[n].split("/")[2]).split(".")[0]).split("_")

	for line in g:
		time_point.append(float(line.split(",")[0]))

	time_point.sort()
	print time_point

	times = []

	for i in range(len(time_point)-1):
		avg = (time_point[i]+time_point[i+1])/2
		times.append(avg-1)
		times.append(avg+1)

	print times

	idx = 0

	total_power = 0.0
	total_time = 0.0

	start = False
	c = 0

	f.readline() # To remove the strings in the first line.
	title = ["base", "base", "encrypt", "encrypt", "base", "base", "decrypt", "decrypt", "base", "base"]
	avg_powers = []
	max_powers = []
	min_powers = []
	avg_base = 0
	avg_enc = (time_point[2] - time_point[1])/float(s[3])
	avg_dec = (time_point[4] - time_point[3])/float(s[3])

	for line in f:
		time = float(line.split(",")[0])
		gap = times[idx] - time

		if (idx % 2 == 0) and (gap > 0) and (gap < time_slice) and (not start):
			gap = 0.0002 - gap
			if isFloat(line.split(",")[3][0:-2]) == True:
				avg_power = float(line.split(",")[3][0:-2])
			else:
				print "An important time is error"
				break
			print "%s start: %f, %f" % (title[idx], time + gap, avg_power)
			start = True
			total_power = 0
			total_time = 0
			max_power = 0
			min_power = 10000
			total_power = total_power + time_slice * avg_power
			total_time = total_time + time_slice
			idx = idx + 1
		elif (idx % 2 == 1) and (gap > 0) and (gap < time_slice) and start:
			if isFloat(line.split(",")[3][0:-2]) == True:
				avg_power = float(line.split(",")[3][0:-2])
			else:
				print "An important time is error"
				break
			print "%s end: %f, %f" % (title[idx], time + gap, avg_power)
			start = False
			total_power = total_power + time_slice * avg_power
			total_time = total_time + time_slice
			
			avg_powers.append(total_power/total_time)
			max_powers.append(max_power)
			min_powers.append(min_power)	
#			out_file.write("%s power: \t%.2f (max: %.2f, min: %.2f)\n" % (title[idx], total_power/total_time, max_power, min_power))
			total_power = 0
			total_time = 0
			idx = idx + 1

			if idx == 10:
				out_file.write("%s, %s, %s, %s, %s, %s, %s, %.2lf, %.2lf, %.2lf, %.2lf\n" % (s[0], s[1], s[2], s[3], s[4], s[5], "enc", avg_enc, avg_powers[1]-avg_powers[0], max_powers[1]-avg_powers[0], min_powers[1]-avg_powers[0]))
				out_file.write("%s, %s, %s, %s, %s, %s, %s, %.2lf, %.2lf, %.2lf, %.2lf\n" % (s[0], s[1], s[2], s[3], s[4], s[5], "dec", avg_dec, avg_powers[3]-avg_powers[0], max_powers[3]-avg_powers[0], min_powers[3]-avg_powers[0]))
				break
		elif start:
			if isFloat(line.split(",")[3][0:-2]) == True:
				avg_power = float(line.split(",")[3][0:-2])
			else:
				continue

			if avg_power > max_power:
				max_power = avg_power
			if avg_power < min_power:
				min_power = avg_power
			total_power = total_power + time_slice * avg_power
			total_time = total_time + time_slice
		else:
			continue
			
f.close()
g.close()
out_file.close()
