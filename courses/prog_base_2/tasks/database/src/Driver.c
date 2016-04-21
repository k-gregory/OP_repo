#include "Driver.h"

#include "QueryingUtil.h"

#include <sqlite3.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

static char* copy_string(char* orig){
    if(orig == NULL) return NULL;
    char* ret=  malloc(strlen(orig)+1);
    strcpy(ret,orig);
    return ret;
}


Driver* driver_create(char* name,
                      char* surname,

                      char* car_manufacturer,
                      char* car_model,
                      double car_average_speed,

                      double km_fare,

                      unsigned int satisfied_clients,
                      unsigned int unsatisfied_clients,

                      time_t hired_at) {
    if(NULL== name ||
       NULL == surname ||
       NULL == car_manufacturer ||
       NULL == car_model) return NULL;

    Driver* ret = malloc(sizeof(Driver));

    ret->id = 0;

    ret->name = copy_string(name);
    ret->surname = copy_string(surname);

    ret->car_manufacturer = copy_string(car_manufacturer);
    ret->car_model = copy_string(car_model);
    ret->car_average_speed =  car_average_speed;

    ret->km_fare = km_fare;

    ret->satisfied_clients = satisfied_clients;
    ret->unsatisfied_clients = unsatisfied_clients;

    ret->hired_at = hired_at;

    return ret;
}

SaveStatus driver_save(sqlite3* db, Driver* driver) {
    SaveStatus status;

    def_stmt("insert into Driver(name,surname,car_manufacturer,car_model,car_average_speed,km_fare,satisfied_clients,unsatisfied_clients,hired_at)"
              "values (@name,@surname,@c_manufacturer,@c_model,@c_avg_speed,@km_fare,@sat_clients,@unsat_clients,@hired_at)");

    bind_text_v("@name",driver->name);
    bind_text_v("@surname",driver->surname);

    bind_text_v("@c_manufacturer",driver->car_manufacturer);
    bind_text_v("@c_model",driver->car_model);
    bind_double_v("@c_avg_speed",driver->car_average_speed);

    bind_double_v("@km_fare",driver->km_fare);

    bind_int_v("@sat_clients",driver->satisfied_clients);
    bind_int_v("@unsat_clients", driver->unsatisfied_clients);

    bind_int64_v("@hired_at",driver->hired_at);

    status = sqlite3_step(q) == SQLITE_DONE ? SAVE_OK : SAVE_FAIL;
    driver->id = sqlite3_last_insert_rowid(db);

    sqlite3_reset(q);

    return status;
}

Driver* driver_find_by_id(sqlite3* db, sqlite3_int64 id){
    Driver* ret;
    def_stmt("select name,surname,car_manufacturer,car_model,car_average_speed,km_fare,satisfied_clients,unsatisfied_clients,hired_at "
             "from Driver where id = @id");

    bind_id_v("@id", id);

    if(sqlite3_step(q)!=SQLITE_ROW) return NULL;

    ret = driver_create(col_text(0),col_text(1),col_text(2),col_text(3),col_double(4),col_double(5),col_int(6),col_int(7),col_int64(8));
    ret->id = id;

    sqlite3_reset(q);
    return ret;
}

void driver_update(sqlite3* db, Driver* driver){
    def_stmt("update Driver set "
             "name = @name,"
             "surname = @surname,"
             "car_manufacturer=@c_manufacturer,"
             "car_model=@c_model,"
             "car_average_speed=@c_avg_speed,"
             "km_fare=@km_fare,"
             "satisfied_clients=@sat_clients,"
             "unsatisfied_clients=@unsat_clients,"
             "hired_at=@hired_at "
             "where id = @id");

    bind_id_v("@id", driver->id);

    bind_text_v("@name",driver->name);
    bind_text_v("@surname",driver->surname);

    bind_text_v("@c_manufacturer",driver->car_manufacturer);
    bind_text_v("@c_model",driver->car_model);
    bind_double_v("@c_avg_speed",driver->car_average_speed);

    bind_double_v("@km_fare",driver->km_fare);

    bind_int_v("@sat_clients",driver->satisfied_clients);
    bind_int_v("@unsat_clients", driver->unsatisfied_clients);

    bind_int64_v("@hired_at",driver->hired_at);

    sqlite3_step(q);
    sqlite3_reset(q);
}

unsigned int driver_count(sqlite3 *db){
    unsigned int res;
    def_stmt("select count(id) from Driver");
    sqlite3_step(q);
    res = col_int(0);
    sqlite3_reset(q);
    return res;
}

void driver_delete(sqlite3* db, Driver* driver){
    def_stmt("delete from Driver where id = @id");

    bind_id_v("@id", driver->id);

    sqlite3_step(q);
    sqlite3_reset(q);
}

void driver_filtered(sqlite3* db, double maxKmFare, time_t minStage,void (*callback)(Driver*)){
    def_stmt("select name,surname,car_manufacturer,car_model,car_average_speed,km_fare,satisfied_clients,unsatisfied_clients,hired_at,id "
             "from Driver where km_fare < @maxKmFare and (strftime('%s','now')-hired_at) > @minStage");

    bind_double_v("@maxKmFare",maxKmFare);
    bind_int64_v("@minStage",minStage);

    while(sqlite3_step(q) == SQLITE_ROW){
        Driver* d;
        d = driver_create(col_text(0),col_text(1),col_text(2),col_text(3),col_double(4),col_double(5),col_int(6),col_int(7),col_int64(8));
        d->id = col_id(9);
        callback(d);
    }
    sqlite3_reset(q);
}
