[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent "App";

let make ::route _children => {
  ...component,
    render: fun _self => {
      let page = switch route {
        | Routes.Front => <FrontPage />
        | Routes.Comments id => <CommentsPage id />
      };
    <div> page </div>
  }
};


