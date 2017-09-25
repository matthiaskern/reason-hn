let component = ReasonReact.statelessComponent "FrontPage";

let make  _children => {
  ...component,
  render: fun _self =>
    <div className="App">
      <div className="App-header">
        <h2> (ReasonReact.stringToElement "Reason HN") </h2>
      </div>
      <p className="App-intro">
      </p>
    </div>
};
