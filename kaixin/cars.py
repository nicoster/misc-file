def main(cars):
	cars2={}
	
	for car in cars:
		cars2[car['park_uid']]=car
		
	return cars2
	
	
	
	
	