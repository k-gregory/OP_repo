(function(){
    var app = angular.module("cabService",[])
    app.controller('cabsController', function(){
	this.drivers = drivers;
    })
    drivers = [{
	name : "Dead Moroze",
	kmFare : 43.6,
	workStartDate: "New Year",
	satisfiedClients: 1,
	unsatisfiedClients: 42,
	averageSpeed: 0
    }]
})();
