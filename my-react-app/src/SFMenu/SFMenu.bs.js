'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");

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
  return React.createElement("div", undefined, React.createElement("p", undefined, "Hello"), typeof state === "number" ? (
                state !== 0 ? "Unabled to load data" : "Loading..."
              ) : "Loaded");
}

var make = SFMenu;

exports.Decode = Decode;
exports.url = url;
exports.make = make;
/* react Not a pure module */
