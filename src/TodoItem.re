let str = React.string;

type item = {
  id: int,
  title: string,
  completed: bool,
};

let toggleItem = (item: item) => {...item, completed: !item.completed};

let toggleId = (itemList, id) =>
  itemList
  |> List.map((item: item) =>
       if (item.id == id) {
         toggleItem(item);
       } else {
         item;
       }
     );

let lastId = ref(0);
let newItem = (title: string): item => {
  lastId := lastId^ + 1;
  {id: lastId^, title, completed: false};
};

[@react.component]
let make = (~item, ~onToggle) =>
  <div
    className="item"
    onClick={
      _ev => {
        ReactEvent.Synthetic.preventDefault(_ev);
        onToggle(item);
      }
    }>
    <label>
      <input type_="checkbox" checked={item.completed} readOnly=true />
      {str(item.title)}
    </label>
  </div>;
