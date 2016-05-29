(function(){
    var app = angular.module("cabService",[])
    app.service('DriversDataService', ["$http", function($http){	
	var self = this
	self.drivers = []

	function fetchDrivers(){
	    $http.get("/api/drivers").then(
		function onSuccess(res){
		    self.drivers = res.data
		},
		function onError(msg){
		    console.log(msg)
		}
	    )
	}
	fetchDrivers()

	self.addDriver = function(driver){
	    $http.post("/api/drivers",driver).then(
		function onSuccess(res){
		    self.drivers.push(driver)
		},
		function onError(msg){
		    console.log(msg)
		}
	    )
	}
	self.deleteDriver = function(driver){
	    $http.delete("/api/drivers/"+driver.index).then(
		function onSuccess(res){
		    var delIndex = self.drivers.indexOf(driver)
		    self.drivers.splice(delIndex, 1)
		}
	    )
	}
    }])
    
    app.controller('CabsController', ["$scope","DriversDataService", function($scope,DriversDataService){
	$scope.drivers = DriversDataService.drivers
	$scope.$watchCollection(function(){ return DriversDataService},function(oldVal, newVal){
	    $scope.drivers = DriversDataService.drivers
	})
	$scope.deleteDriver = function(driver){
	    DriversDataService.deleteDriver(driver)
	}
    }])
    app.controller('DriverController', ["$scope","DriversDataService", function($scope,DriversDataService){
	function getInitialDriver(){
	    var initialDriver = {
		index:0,
		kmFare: 15,
		satisfiedClients: 0,
		unsatisfiedClients:0,
		workStartDate: new Date().toLocaleDateString(),
		averageSpeed: 60
	    }

	    return jQuery.extend({}, initialDriver)
	}
	$scope.newDriver = getInitialDriver()

	$scope.reset = function(){
	    $scope.newDriver = getInitialDriver()
	    $scope.driverForm.$setPristine()
	}		       
	
	$scope.addDriver = function(){
	    DriversDataService.addDriver($scope.newDriver)	    
	    $scope.reset()
	}
    }])
})();
