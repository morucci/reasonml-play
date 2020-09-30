'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var ReactBootstrapMinJs = require("react-bootstrap/dist/react-bootstrap.min.js");

var Button = {};

function decodeMenuEntry(menuEntry) {
  return {
          name: Json_decode.field("name", Json_decode.string, menuEntry),
          path: Json_decode.field("path", Json_decode.string, menuEntry)
        };
}

function decodeMenuEntries(json) {
  return Json_decode.list(decodeMenuEntry, json);
}

var Decode = {
  decodeMenuEntry: decodeMenuEntry,
  decodeMenuEntries: decodeMenuEntries
};

var url = "http://localhost:8001/menu.json";

function SFMenu(Props) {
  var match = React.useState(function () {
        return /* Loading */0;
      });
  var setState = match[1];
  var state = match[0];
  var fetchMenuEntries = function (param) {
    return fetch(url).then(function (prim) {
                    return prim.json();
                  }).then(function (json) {
                  var entries = Json_decode.list(decodeMenuEntry, json);
                  return Promise.resolve(Curry._1(setState, (function (param) {
                                    return /* Success */{
                                            _0: entries
                                          };
                                  })));
                }).catch(function (_err) {
                return Promise.resolve(Curry._1(setState, (function (param) {
                                  return /* Failure */1;
                                })));
              });
  };
  React.useEffect((function () {
          fetchMenuEntries(undefined);
          
        }), []);
  var displayEntry = function (i, entry) {
    return React.createElement("li", {
                key: String(i)
              }, entry.name + (" " + entry.path));
  };
  return React.createElement("div", undefined, React.createElement("p", undefined, "Hello"), typeof state === "number" ? (
                state !== 0 ? "Unabled to load data" : "Loading..."
              ) : React.createElement("div", undefined, React.createElement(ReactBootstrapMinJs.Button, {
                        variant: "primary",
                        children: "Test"
                      }), React.createElement("ul", undefined, Belt_Array.mapWithIndex(Belt_List.toArray(state._0), displayEntry))));
}

var make = SFMenu;

exports.Button = Button;
exports.Decode = Decode;
exports.url = url;
exports.make = make;
/* react Not a pure module */
