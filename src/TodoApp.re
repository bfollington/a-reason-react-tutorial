let str = React.string;

type state = {items: list(TodoItem.item)}

type action =
  | Add(TodoItem.item)
  | ToggleCompletion(TodoItem.item)
  | Remove;

[@react.component]
let make = (~title) => {
  let ({items}: state, dispatch) =
    React.useReducer(
      (s, a) =>
        switch (a) {
        | Add(todo) => {items: [todo, ...s.items]}
        | ToggleCompletion(todo) => {items: TodoItem.toggleId(s.items, todo.id)}
        | Remove => s
        },
      {items: [{id: 0, title: "It's a todo!", completed: false}]},
    );

  let itemCount = items |> List.length |> string_of_int |> str;

  <div className="app">
    <div className="title"> {str(title)} </div>
    <TodoInput onCreate={text => dispatch(Add(TodoItem.newItem(text)))} />
    <div className="items"> {str("Nothing")} </div>
    {
      items
      |> List.map((item: TodoItem.item) =>
           <TodoItem
             key={string_of_int(item.id)}
             item
             onToggle={todo => dispatch(ToggleCompletion(todo))}
           />
         )
      |> Array.of_list
      |> React.array
    }
    <div className="footer"> itemCount </div>
  </div>;
};