let str = React.string;
let valueFromEvent = evt: string => evt->ReactEvent.Form.target##value;

[@react.component]
let make = (~onCreate) => {
  let (text, setText) = React.useReducer((_, newText) => newText, "");

  <div className="input">
    <input
      type_="text"
      value=text
      onChange={_ev => setText(valueFromEvent(_ev))}
    />
    <button
      onClick={
        _ev => {
          onCreate(text);
          setText("");
        }
      }>
      {str("Add Todo")}
    </button>
  </div>;
};