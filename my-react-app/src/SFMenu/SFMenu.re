// module MyBrand = {
//   [@bs.module]
//   external mybrand: ReasonReact.reactClass = "react-bootstrap/lib/NavbarBrand";

//   [@bs.obj]
//   external mybrandProps: (~href: string=?, ~bsPrefix: string=?, unit) => _;

//   [@react.component]
//   let make = (~href=?, ~bsPrefix=?, ~children) =>
//     ReasonReact.wrapJsForReason(
//       ~reactClass=mybrand,
//       ~props=mybrandProps(~href?, ~bsPrefix?, ()),
//       children,
//     );
// };

// module MY2 = {
//   [@bs.module "react-bootstrap/lib/NavbarBrand"] [@react.component]
//   external make: (~href: string=?, ~bsPrefix: string=?) => React.element =
//     "default";
// };
// module Component: {
//   type t;
//   let string: string => t;
//   let callback: (unit => React.element) => t;
//   let element: React.element => t;
// } = {
//   [@unboxed]
//   type t =
//     | Any('a): t;
//   let string = (v: string) => Any(v);
//   let callback = (v: unit => React.element) => Any(v);
//   let element = (v: React.element) => Any(v);
// };

// module MY2 = {
//   [@react.component] [@bs.module "react-bootstrap/lib/NavbarBrand"]
//   external make: (~component: Component.t=?, ~href: string=?, ~bsPrefix: string=?, ~children: 'children=?) => React.element = "Branc"
// }

module Button = {
  // [@bs.module "@patternfly/react-core/dist/umd/react-core.min.js"]
  [@react.component] [@bs.module "react-bootstrap/dist/react-bootstrap.min.js"]
  external make: (~variant: string, ~children: 'children=?) => React.element =
    "Button";
};

type menuEntry = {
  name: string,
  path: string,
};

type state =
  | Loading
  | Success(list(menuEntry))
  | Failure;

module Decode = {
  let decodeMenuEntry = (menuEntry): menuEntry =>
    Json.Decode.{
      name: field("name", string, menuEntry),
      path: field("path", string, menuEntry),
    };
  let decodeMenuEntries = (json): list(menuEntry) =>
    Json.Decode.list(decodeMenuEntry, json);
};

let url: string = "http://localhost:8001/menu.json";

// let navbar = Navbar.make(~fixed=`top, ~fluid=true, ~collapseOnSelect=true);

// let url: string = "http://localhost:8001/menu.json";
// let component = "App" |> ReasonReact.statelessComponent;
// let make = _children => {
//   ...component,
//   render: _self =>
//     <div className="App container">
//       <mynav>
//         <mynav.Brand href="https:://">
//           <p> {React.string("test")} </p>
//         </mynav.Brand>
//         <Navbar.Toggle />
//         <Navbar.Collapse>
//           <Nav pullRight=true>
//             <Nav.Item href="signup"> {string("Sign Up")} </Nav.Item>
//             <Nav.Item href="login"> {string("Log In")} </Nav.Item>
//           </Nav>
//         </Navbar.Collapse>
//       </mynav>
//       // <MY2> <a href="/"> {string("Scratch")} </a> </MY2>
//       <Routes />
//     </div>,
// };

[@react.component]
let make = () => {
  let (state, setState) = React.useState(() => Loading);
  let fetchMenuEntries = () =>
    Js.Promise.(
      Fetch.fetch(url)
      |> then_(Fetch.Response.json)
      |> then_(json =>
           json
           |> Decode.decodeMenuEntries
           |> (entries => setState(_ => Success(entries)))
           |> resolve
         )
      |> catch(_err => setState(_ => Failure) |> resolve)
    );

  React.useEffect0(() => {
    let _ = fetchMenuEntries();
    None;
  });

  let displayEntry = (i: int, entry: menuEntry) =>
    <li key={Belt.Int.toString(i)}>
      {React.string(entry.name ++ " " ++ entry.path)}
    </li>;

  <div>
    <p> {React.string("Hello")} </p>
    {switch (state) {
     | Loading => React.string("Loading...")
     | Failure => React.string("Unabled to load data")
     | Success(entries) =>
       <div>
         <Button variant="primary"> {React.string("Test")} </Button>
         <ul>
           {Belt.Array.mapWithIndex(Belt.List.toArray(entries), displayEntry)
            |> React.array}
         </ul>
       </div>
     }}
  </div>;
};
