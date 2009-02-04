import time

# the car parked in space owned by neighbours or space with higher fee rate should take precedence
def getNextToPark(cars, park_uid):
	#~ print park_uid
	car_groups = {}
	now = time.time()

	print 'cars to pack:'
	for car in cars:
		#~ print car['park_uid']
		if int(car['park_uid']) == int(park_uid):
			continue
			
		if car['ctime'] + 20 * 60 < now or car['park_uid'] == 0:
			if not car_groups.has_key(car['park_uid']):
				car_groups[car['park_uid']]=[]
				#~ print car['park_uid'], car['park_real_name']
				
			car_groups[car['park_uid']].append(car)
			print car['park_real_name'], car['car_name']
			
	candidate = {}
	max_count = 0
	for (k, car_group) in car_groups.items():
		if len(car_group) > max_count:
			max_count = len(car_group)
			candidate = car_group[0]
			for car in car_group:
				if car['neighbor'] == '1':
					candidate = car
					break
					
		if len(car_group) == max_count and candidate['neighbor'] != '1':
			for car in car_group:
				if car['neighbor'] == '1':
					candidate = car
					break
			
	if candidate:
		print 'return', candidate['park_real_name'], candidate['car_name'], candidate['neighbor']
	else:
		print 'return nothing'
	return candidate
	
	
	
	
	