
var utf8 = /^[\u0020-\u007e\u00a0-\u00ff\u0410-\u04d9\ufe8e-\ufef1\u10A8-\u10A9\u0531-\u0586\u1B05-\u1B4B\u1BC0-\u1BF3\u0985-\u09CD\u1000-\u1060\u1A00-\u1A1F\u0041-\u005a\u16a0-\u16f8\u2c00-\u2c2a\u0391-\u03C9\u10D0-\u10F0\u05d0-\u05ea\u4e00-\u9fff\u3105–\u312D\u0070–\u02AF]*$/;
let envar = "abcdefghijklmnopqrstuvwxyz"
let ruvar = "абвгдежзийклмнопрстуфхцчшщъыьэюя"
let numvar = "0123456789"
let messvar = "@#$%^&*()_+-=,./<>?!"
let pvar = "\n\r";
var count_h = 0;

const webSocket = new WebSocket('ws://localhost:8081');

webSocket.onmessage = function(e) {
  if (e.data.toString() == "true") {
    window.localStorage.clear();
    window.localStorage.setItem('flag', 'true');
    window.location.pathname = "/admin_page.html";
    //setTimeout(() => { window.localStorage.clear(); }, 3600000);
  }
  else
    if (e.data.toString() == "false") {
      window.localStorage.clear();
      window.localStorage.setItem('flag', 'false');
      window.location.pathname = "/drivers.html";
      //setTimeout(() => { window.localStorage.clear(); }, 3600000);
    }
    else
      if ((e.data[0] != "w") && (e.data[0] != "u") && (e.data[0] != "r") && (e.data != "nope")) showMessage(e.data);
      else
      {
        if (e.data[0] == "w") parse("1", e.data.substring(1, e.data.length));
        if (e.data[0] == "r") parse("2", e.data.substring(1, e.data.length));
        if (e.data[0] == "u") parse("3", e.data.substring(1, e.data.length));
      }
}

function parse(type, send) {
  if (type == "1") {
    console.log("1...........");
    let ans = JSON.parse(send);
    webSocket.send(`id=w1&data=${send}`);
    /*document.getElementById('application_table').innerHTML = '';
    for (var i = 0; i < ans.length; i++) {
      if (ans[i].flag.toString() == "false") {
        console.log("true");
      document.getElementById('application_table').innerHTML =
        document.getElementById('application_table').innerHTML +
        `<tr>
          <td>${ans[i].name}</td>
          <td>${ans[i].number}</td>
          <td>${ans[i].email}</td>
          <td>${ans[i].message}</td>
          <td><button onclick ="dtnch(${type}, ${ans[i].id})" id="report_button" >Просмотр</button></td>
        </tr>`;
      }
    }
    for (var i = 0; i < ans.length; i++) {
      if (ans[i].flag.toString() == "true") {
      document.getElementById('application_table').innerHTML =
        document.getElementById('application_table').innerHTML +
        `<tr>
          <td>${ans[i].name}</td>
          <td>${ans[i].number}</td>
          <td>${ans[i].email}</td>
          <td>${ans[i].message}</td>
          <td>Просмотрено</td>
        </tr>`;
      }
    }*/
  }

    if (type == "2") {
      console.log("2...........");
      let ans = JSON.parse(send);
      webSocket.send(`id=r1&data=${send}`);
      /*document.getElementById('report_table').innerHTML = '';
      for (var i = 0; i < ans.length; i++) {
        if (ans[i].flag.toString() == "false") {
        document.getElementById('report_table').innerHTML =
          document.getElementById('report_table').innerHTML +
          `<tr>
            <td>${ans[i].name}</td>
            <td>${ans[i].date}</td>
            <td>${ans[i].profil}</td>
            <td>${ans[i].car}</td>
            <td>${ans[i].mileage}</td>
            <td>${ans[i].station}</td>
            <td>${ans[i].expenses}</td>
            <td>${ans[i].message}</td>
            <td><button onclick ="dtnch(${type}, ${ans[i].id})" id="report_button" >Просмотр</button></td>
          </tr>`;
        }
      }
      for (var i = 0; i < ans.length; i++) {
        if (ans[i].flag.toString() == "true") {
        document.getElementById('report_table').innerHTML =
          document.getElementById('report_table').innerHTML +
          `<tr>
            <td>${ans[i].name}</td>
            <td>${ans[i].date}</td>
            <td>${ans[i].profil}</td>
            <td>${ans[i].car}</td>
            <td>${ans[i].mileage}</td>
            <td>${ans[i].station}</td>
            <td>${ans[i].expenses}</td>
            <td>${ans[i].message}</td>
            <td>Просмотрено</td>
          </tr>`;
        }
      }*/
    }

    if (type == "3") {
      console.log("3...........");
      let ans = JSON.parse(send);
      webSocket.send(`id=u1&data=${send}`);
      /*document.getElementById('user_table').innerHTML = '';
      for (var i = 0; i < ans.length; i++) {
      document.getElementById('user_table').innerHTML =
        document.getElementById('user_table').innerHTML +
        `<tr>
          <td>${ans[i].name}</td>
          <td>${ans[i].phone}</td>
          <td>${ans[i].date}</td>
          <td>${ans[i].login}</td>
          <td>${ans[i].password}</td>
        </tr>`;
      }*/
    }
}

function dtnch(t, id) {
  if (t == "1") webSocket.send(`id=changework&el=${id}`);
  if (t == "2") webSocket.send(`id=changereport&el=${id}`);
  if (t == "3") document.location.href = "new_person.html";
}

function utfcheck(string_) {
  var mis = 0;
  for (var i = 0; i < string_.length; i++) {
    if (string_[i].match(utf8) != null)
      mis += 1;
  }
  if (string_.length == mis)
    //console.log("true");
    return(true)
  else
    //console.log("false");
    return(false)
}

function check(string, type) {
  var flag_input = "false";
  string = string.toLowerCase();
  var misvar = 0;
  for (let i = 0; i < string.length; i++) {
    for (let j = 0; j < type.length; j++) {
      if (string[i] == type[j]) misvar++;
    }
  }
  if (misvar == string.length) flag_input = "true";
  return(flag_input);
}

function notnull(string) {
  string = string.replace(/\s{2,}/g, ' ');
  string.trim();
  if ((string == " ") || (string == "\u00A0") || (string == "\n")) string = "";

  return(string);
}

function showMessage(message) {
  let messageElem = document.createElement('div');
  messageElem.textContent = message;
  if (document.getElementById('messages').hasChildNodes())
    document.getElementById('messages').innerHTML = '';
  document.getElementById('messages').prepend(messageElem);
  document.getElementById('messages_back').classList.remove("invisible");
  document.getElementById('messages_back').classList.add("visible");
  setTimeout(() => {
    document.getElementById('messages').removeChild(messageElem);
    document.getElementById('messages_back').classList.add("invisible");
  }, 50000);
}

function a_btn_onclick() {
  let inputp = document.querySelector("#inputpas")
  let inputl = document.querySelector("#inputlog")
  inputl.value = notnull(inputl.value);
  inputp.value = notnull(inputp.value);
  let mislogin = envar + ruvar + numvar + messvar;
  let mispass = envar + ruvar + numvar + messvar;
  if ((inputp.value == "") || (inputl.value == ""))
      showMessage('Вы заполнили не все обязательные поля');
  else {
    if (true)
      if (true) {
        var auto_string = `id=autorization&login=${inputl.value}&password=${inputp.value}`;
        webSocket.send(auto_string);
      }
      else showMessage("Некорректно введен пароль");
    else showMessage("Некорректно введен логин");
  }
}

function h_btn_onclick() {
  let input_name = document.querySelector("#h_name");
  let input_email = document.querySelector("#h_email");
  let input_phone = document.querySelector("#h_phone");
  let input_message = document.querySelector("#h_message");

  input_name.value = notnull(input_name.value);
  input_email.value = notnull(input_email.value);
  input_phone.value = notnull(input_phone.value);
  input_message.value = notnull(input_message.value);

  utfcheck(input_name.value);

  let mis_email = envar + ruvar + messvar + numvar;
  let mis_phone = numvar;
  if ((input_name.value == "") || (input_phone.value == ""))
      showMessage('Вы заполнили не все обязательные поля');
  else {
    if (utfcheck(input_name.value).toString() == "true") {
      if (check(input_email.value, mis_email).toString() == "true") {
        if ((check(input_phone.value, mis_phone).toString() == "true") && (input_phone.value.length == 11)) {
          if (utfcheck(input_message.value).toString() == "true") {
            var auto_string = `id=home&${input_name.name}=${input_name.value}&${input_email.name}=${input_email.value}&${input_phone.name}=${input_phone.value}&${input_message.name}=${input_message.value}`;
            count_h = count_h + 1;
            console.log(count_h);
            setTimeout(() => { count_h = 0; }, 3000);
            if (count_h <= 1) webSocket.send(auto_string);
            else {
              //count_h = 0;
              showMessage("Слишком много попыток");
            }
          }
          else showMessage("Некорректно введено сообщение");
        }
        else showMessage("Некорректно введен номер телефона (формат: 79123456780).");
      }
      else showMessage("Некорректно введен E-mail.");
    }
    else showMessage("Некорректно введено имя.");
  }
}

function d_btn_onclick() {
  let input_name = document.querySelector("#r_name")
  let input_date = document.querySelector("#r_date")
  let input_profil = document.querySelector("#r_profil")
  let input_car = document.querySelector("#r_car")
  let input_mileage = document.querySelector("#r_mileage")
  let input_station = document.querySelector("#r_station")
  let input_expenses = document.querySelector("#r_expenses")
  let input_message = document.querySelector("#r_message")

  input_name.value = notnull(input_name.value);
  input_date.value = notnull(input_date.value);
  input_profil.value = notnull(input_profil.value);
  input_car.value = notnull(input_car.value);
  input_mileage.value = notnull(input_mileage.value);
  input_station.value = notnull(input_station.value);
  input_expenses.value = notnull(input_expenses.value);
  input_message.value = notnull(input_message.value);

  let mis_date = new Date();
  let mis_car = envar + ruvar + numvar + " ";
  let mis_mileage = numvar;
  let mis_station = numvar;
  let mis_expenses = numvar;

  if (input_station.value.toString() == "") input_station.value = 0;
  if ((input_name.value == "") || (input_date.value == "") || (input_profil.value == "") || (input_car.value == "") || (input_mileage.value == ""))
    showMessage('Вы заполнили не все обязательные поля');
  else {
    if (utfcheck(input_name.value).toString() == "true") {
      if (input_date.value <= mis_date.toISOString()) {
        if (utfcheck(input_profil.value).toString() == "true") {
          if (check(input_car.value, mis_car).toString() == "true") {
            if (check(input_mileage.value, mis_mileage).toString() == "true") {
              if (check(input_station.value, mis_station).toString() == "true") {
                if (check(input_expenses.value, mis_expenses).toString() == "true") {
                  if (utfcheck(input_message.value).toString() == "true") {
                    var auto_string = `id=drivers&${input_name.name}=${input_name.value}&${input_date.name}=${input_date.value}&${input_profil.name}=${input_profil.value}&${input_car.name}=${input_car.value}&${input_mileage.name}=${input_mileage.value}&${input_station.name}=${input_station.value}&${input_expenses.name}=${input_expenses.value}&${input_message.name}=${input_message.value}`;
                    webSocket.send(auto_string);
                  }
                  else showMessage("Введите корректный комментарий к работе (разрешенные символы: а-яё А-ЯЁ 0-9 - , . ? ! * =).");
                }
                else showMessage("Введите корректные дополнительные рассходы (разрешенные символы: а-яё А-ЯЁ 0-9 - , . ? ! * =).");
              }
              else showMessage("Введите корректную сумму заправки (разрешенные символы: 0-9).");
            }
            else showMessage("Введите корректный пробег (разрешенные символы: 0-9).");
          }
          else showMessage("Введите корректное наименование машины (формат: Datsun123).");
        }
        else showMessage("Введите корректный профиль (разрешенные символы: А-Я и а-я).");
      }
      else showMessage("Введите корректную дату.");
    }
    else showMessage("Введите корректное ФИО (разрешенные символы: А-Я и а-я).");
  }
}

function np_btn_onclick() {
  let input_name = document.querySelector("#np_name")
  let input_date = document.querySelector("#np_date")
  let input_phone = document.querySelector("#np_phone")
  let input_login = document.querySelector("#np_login")
  let input_password = document.querySelector("#np_password")

  input_name.value = notnull(input_name.value);
  input_phone.value = notnull(input_phone.value);
  input_login.value = notnull(input_login.value);
  input_password.value = notnull(input_password.value);

  let mis_name = envar + ruvar + " -";
  let mis_date = new Date();
  let mis_phone = numvar;
  let mis_login = envar + ruvar + messvar + numvar;
  let mis_password = envar + ruvar + messvar + numvar;

  if ((input_name.value == "") || (input_date.value == "") || (input_phone.value == "") || (input_password.value == "") || (input_login.value == ""))
    showMessage('Вы заполнили не все обязательные поля');
  else {
    if (check(input_name.value, mis_name).toString() == "true") {
      if (input_date.value <= mis_date.toISOString()) {
        if ((check(input_phone.value, mis_phone).toString() == "true") && (input_phone.value.length == 11)) {
          if (check(input_login.value, mis_login).toString() == "true") {
            if (check(input_password.value, mis_password).toString() == "true") {
              var auto_string = `id=new_person&${input_name.name}=${input_name.value}&${input_date.name}=${input_date.value}&${input_phone.name}=${input_phone.value}&${input_login.name}=${input_login.value}&${input_password.name}=${input_password.value}`;
              webSocket.send(auto_string);
            }
            else showMessage("Введите корректный пароль (разрешенные символы: a-z A-Z 0-9 @ - _ *).");
          }
          else showMessage("Введите корректный логин (разрешенные символы: a-z A-Z 0-9 @ - _ *).");
        }
        else showMessage("Введите корректный номер телефона (разрешенные символы: 0-9, формат: 79123456780).");
      }
      else showMessage("Введите корректную дату.");
    }
    else showMessage("Введите корректное ФИО (разрешенные символы: А-Я и а-я).");
  }
}

//////////////////////////////////////////////////////
function idd_click() {
  webSocket.send(`id=admin`);
}

if (window.performance) {
  console.log(">>>");
  webSocket.onopen = () => webSocket.send(`id=admin`);
  let flag_admin = window.localStorage.getItem('flag');
  if (flag_admin != null) {
    if (flag_admin.toString() == "true") {
      if (window.location.pathname == "/admin_page.html")
        //webSocket.onopen = () => webSocket.send(`id=admin`);
      document.getElementById('addli').classList.remove("invisible");
      document.getElementById('addli').classList.add("visible");
      document.getElementById('addli').textContent = "Администратор";
      document.getElementById('navauto').textContent = "Выйти";
      document.getElementById('addli').href = "admin_page.html";
      if (window.location.pathname == "/autorization.html") {
        document.getElementById('addli').classList.remove("visible");
        document.getElementById('addli').classList.add("invisible");
        document.getElementById('navauto').textContent = "Авторизация";
        window.localStorage.clear();
      }
    }
    else if (flag_admin.toString() == "false") {
      document.getElementById('addli').classList.remove("invisible");
      document.getElementById('addli').classList.add("visible");
      document.getElementById('addli').textContent = "Водителям";
      document.getElementById('navauto').textContent = "Выйти";
      document.getElementById('addli').href = "drivers.html";
      if (window.location.pathname == "/admin_page.html")
        window.location.pathname = "/.admin_page.html";
      if (window.location.pathname == "/autorization.html") {
        document.getElementById('addli').classList.remove("visible");
        document.getElementById('addli').classList.add("invisible");
        document.getElementById('navauto').textContent = "Авторизация";
        window.localStorage.clear();
      }
    }
  }
  else {
    document.getElementById('navauto').textContent = "Авторизация";
    if (window.location.pathname == "/admin_page.html")
      window.location.pathname = "/.admin_page.html";
    if (window.location.pathname == "/drivers.html")
      window.location.pathname = "/.drivers.html";
  }
}
