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
    <li key={Belt.Int.toString(i)}> {React.string(entry.name)} </li>;

  <div>
    <p> {React.string("Hello")} </p>
    {switch (state) {
     | Loading => React.string("Loading...")
     | Failure => React.string("Unabled to load data")
     | Success(entries) =>
       <div>
         <ul>
           {React.array(
              {
                Belt.Array.mapWithIndex(
                  Belt.List.toArray(entries),
                  displayEntry,
                );
              },
            )}
         </ul>
       </div>
     }}
  </div>;
};
