function connectclient() {
  const { Client } = require("pg");
  const client = new Client({
    user: "postgres",
    host: "localhost",
    database: "internet_taxi",
    password: "kvak",
    port: 5432,
  });
  client.connect();
  return client;
}

/* ----------autorization----------*/
module.exports.autorization_db = function b(usersa: any, uauto: any) {
  console.log("autorization");
  let sendans = "nope";
  const client = connectclient();
  client.query(`SELECT * FROM users`, function a(err: any, res: any) {
    if (err) {
      console.error(err);
      return;
    }
    for (const row of res.rows) {
      if (row.login === uauto.login && row.password === uauto.password) {
        sendans = row.flag_admin.toString();
      }
    }
    if (sendans === "nope") sendans = "Такого пользователя не существует";
    for (const u of usersa) u.connection.send(sendans.toString());
  });
};
/* ----------home----------*/
module.exports.home_db = function c(usersh: any, awork: any) {
  const client = connectclient();
  let idwork = 1;
  client.query(`SELECT * FROM work_application`, (err: any, res: any) => {
    if (err) {
      console.error(err);
      return;
    }
    for (const row of res.rows) {
      if (idwork <= row.id) idwork = row.id + 1;
    }
    const insertwork = `INSERT INTO work_application (id, name, number, email, message, flag)
        VALUES (${idwork}, '${awork.work_name.toString()}', '${
      awork.work_tel
    }', '${awork.workemail}','${awork.work_message.toString()}', false);`;
    client.query(insertwork, (err1: any, res1: any) => {
      if (err1) {
        console.error(err1);
        for (const u of usersh) u.connection.send("Произошла ошибка");
        return;
      }
      if (res1)
        for (const u of usersh)
          u.connection.send("Ваша заявка успешна отправлена");
    });
  });
};
/* ----------drivers----------*/
module.exports.drivers_db = function d(usersd: any, dreport: any) {
  const client = connectclient();
  let idreport = 1;
  client.query(`SELECT * FROM report_drivers`, (err: any, res: any) => {
    if (err) {
      console.error(err);
      return;
    }
    for (const row of res.rows) {
      if (idreport <= row.id) idreport = row.id + 1;
    }
    const insertdrivers = `
    INSERT INTO report_drivers (id, name, date, profil, car, mileage, station, expenses, message, flag)
        VALUES (${idreport}, '${dreport.report_name.toString()}', '${
      dreport.report_date
    }', '${dreport.report_profil.toString()}', '${dreport.report_car.toString()}', ${
      dreport.report_mileage
    }, ${
      dreport.report_station
    }, '${dreport.report_expenses.toString()}', '${dreport.report_message.toString()}', false);`;
    client.query(insertdrivers, (err1: any, res1: any) => {
      if (err1) {
        console.error(err1);
        for (const u of usersd) u.connection.send("Произошла ошибка");
        return;
      }
      if (res1)
        for (const u of usersd)
          u.connection.send("Ваш отчет успешно отправлен.");
    });
  });
};
/* ----------new_person----------*/
/* module.exports.newperson_db = function (users_d, u_create) {
    var count_err = 0;
    const { Client } = require('pg');
    const client = new Client({
        user: 'postgres',
        host: 'localhost',
        database: 'internet_taxi',
        password: 'kvak',
        port: 5432,
    });
    client.connect();
    const select_users1 = `SELECT * FROM users`;
    client.query(select_users1, (err:any, res:any) => {
        if (err) {
            console.error(err);
            return;
        }
        for (let row of res.rows) {
            if (row.login == u_create.login_new)
                count_err++;
        }
        if (count_err == 0) {
            const insert_users1 = `
        INSERT INTO users (login, password, flag_admin)
            VALUES ('${u_create.login_new}', '${u_create.password_new}', false);`;
            client.query(insert_users1, (err:any, res:any) => {
                if (err) {
                    console.error(err);
                    return;
                }
                var id_new = 0;
                const select_users1 = `SELECT * FROM users`;
                client.query(select_users1, (err:any, res:any) => {
                    if (err) {
                        console.error(err);
                        return;
                    }
                    var count_err = 0;
                    for (let row of res.rows) {
                        if ((row.login == u_create.login_new) && (row.password == u_create.password_new))
                            id_new = row.id;
                    }
                    const insert_users2 = `
        INSERT INTO info_users (
            id_users,
            name,
            phone,
            date)
            VALUES (${id_new}, '${u_create.name_new.toString()}',
            '${u_create.phone_new}', '${u_create.date_new}');`;
                    client.query(insert_users2, (err:any, res:any) => {
                        if (err) {
                            console.error(err);
                            return;
                        }
                        client.end();
                        for (let u of users_d)
                            u.connection.send("Пользователь успешно создан.");
                    });
                });
            });
        }
        else
            for (let u of users_d)
                u.connection.send("Ошибка. Пользователь с таким логином уже существует.");
    });
};*/

/* ----------adminapplication----------*/
module.exports.adminapplication_db = function n(users: any) {
  let sendans = "";
  const client = connectclient();
  client.query(
    `SELECT * FROM work_application`,
    function o(err: any, res: any) {
      if (err) {
        console.error(err);
        return;
      }
      sendans = `w${JSON.stringify(res.rows)}`;
      for (const u of users) u.connection.send(sendans);
    }
  );
};

module.exports.chapplication_db = function p(users: any, id: any) {
  console.log("function->chapplication_db");
  let sendans = "";
  const client = connectclient();
  client.query(
    `UPDATE work_application SET flag=true WHERE id=${id}`,
    (err: any, res: any) => {
      if (err) {
        console.error(err);
        return;
      }
      if (res)
        client.query(
          `SELECT * FROM work_application`,
          function q(err2: any, res2: any) {
            if (err2) {
              console.error(err2);
              return;
            }
            if (res2) {
              sendans = `w${JSON.stringify(res.rows)}`;
              for (const u of users) u.connection.send(sendans);
            }
          }
        );
    }
  );
};

/* ----------adminreport----------*/
module.exports.adminreport_db = function e(users: any) {
  console.log("function->adminreport_db");
  let sendans = "";
  const client = connectclient();
  client.query(`SELECT * FROM report_drivers`, function f(err: any, res: any) {
    if (err) {
      console.error(err);
      return;
    }
    sendans = `r${JSON.stringify(res.rows)}`;
    for (const u of users) u.connection.send(sendans);
  });
};
module.exports.chreport_db = function j(users: any, id: number) {
  console.log("function->chreport_db");
  let sendans = "";
  const client = connectclient();
  client.query(
    `UPDATE report_drivers SET flag=true WHERE id=${id}`,
    (err: any, res: any) => {
      if (err) {
        console.error(err);
        return;
      }
      if (res)
        client.query(
          `SELECT * FROM report_drivers`,
          function h(err7: any, res7: any) {
            if (err7) {
              console.error(err7);
              return;
            }
            if (res7) {
              sendans = `r${JSON.stringify(res.rows)}`;
              for (const u of users) u.connection.send(sendans);
            }
          }
        );
    }
  );
};

/* ----------adminuser----------*/
module.exports.adminuser_db = function i(users: any) {
  console.log("function->adminuser_db");
  let sendans = "";
  const client = connectclient();
  const select = `Select users.id, info_users.name, info_users.phone, info_users.date, users.login, users.password
                          from users, info_users
                          where (users.id = info_users.id_users)`;
  client.query(select, function g(err: any, res: any) {
    if (err) {
      console.error(err);
      return;
    }
    sendans = `u${JSON.stringify(res.rows)}`;
    for (const u of users) u.connection.send(sendans);
  });
};

module.exports.chuser_db = function k(users: any, id: any) {
  console.log("function->chreport_db");
  let sendans = "";
  const client = connectclient();
  client.query(
    `UPDATE report_drivers SET flag=true WHERE id=${id}`,
    (err: any, res: any) => {
      if (err) {
        console.error(err);
        return;
      }
      if (res)
        client.query(
          `SELECT * FROM report_drivers`,
          function l(err1: any, res1: any) {
            if (err1) {
              console.error(err1);
              return;
            }
            if (res1) {
              sendans = `r${JSON.stringify(res.rows)}`;
              for (const u of users) u.connection.send(sendans);
            }
          }
        );
    }
  );
};
// # sourceMappingURL=pgdatabase.js.map
