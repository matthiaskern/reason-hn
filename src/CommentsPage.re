let component = ReasonReact.statelessComponent "CommentsPage";

let make ::id _children => {
  ...component,
  render: fun _self =>
    <div className="App">
      <div className="App-header">
        <h2> (ReasonReact.stringToElement "TODO - Comments") </h2>
      </div>
      <p className="App-intro">
        (Utils.textEl (string_of_int id))
      </p>
    </div>
};
