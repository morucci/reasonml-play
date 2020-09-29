let count: int = 43;

let helloWorld = (): string =>
  if (count == 42) {
    "Hello World";
  } else {
    "Hello Fabien";
  };

let hi = helloWorld();

let addOne = (a: int): int => a + 1;
type pair('a, 'b) = ('a, 'b);
let x: pair(int, string) = (1, "ten");
let y: list(string) = ["Hello", "World"];

type gender =
  | Female
  | Male;

type human = {
  name: string,
  age: int,
  sex: gender,
};

let myHuman = {name: "Fabien", age: 36, sex: Male};
let myHuman2 = {name: "Asami", age: 37, sex: Female};
let myHuman3 = {name: "Elsa", age: 5, sex: Female};

let isFemale = (entity: human): bool => {
  switch (entity.sex) {
  | Female => true
  | Male => false
  };
};

// myHuman2.name = "toto"

let myListA = [1, 2, 3];
let myListB = [(-1), 0] @ [999];
let myListC = [1, ...myListA];

let double = List.map(i => i * 2, myListA);

let max =
  List.fold_left(
    (result, item) => item > result ? item : result,
    0,
    myListA,
  );

Js.log(isFemale(myHuman2));

Js.log(hi ++ ", BuckleScript and Reason!");

Js.log(double);
Js.log(max);

type person = {
  name: string,
  age: int
}

let nobody: option(person) = None

let makeCircle = (~x=0, ~y=0, ~radius=0, ()) => {
  x + y * radius
}

makeCircle(~radius=10, ~x=1, ~y=2)
