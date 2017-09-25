open Utils;

[%bs.raw {|require('./CommentsPage.css')|}];

type state = {story_with_comments: option Api.story_with_comments};

let name = "CommentsPage";

type action =
  | Loaded Api.story_with_comments
[@@bs.deriving {accessors: accessors}];

let component = ReasonReact.reducerComponent name;

let make ::id _children => {
  let renderTitle (story: Api.story_with_comments) => {
    let title = <h2 className="CommentsPage_title"> (textEl story.title) </h2>;
    let link =
      switch story.url {
      | Some url => <a href=url className="CommentsPage_titleLink"> title </a>
      | None => title
      };
    <div> link </div>
  };
  let renderByline (story: Api.story_with_comments) =>
    <div>
      <span> (intEl story.score) </span>
      (textEl " points")
      <span>
        <span> (textEl (" submitted " ^ fromNow story.time ^ " by " ^ story.by)) </span>
      </span>
    </div>;
  {
    ...component,
    initialState: fun () => {story_with_comments: None},
    reducer: fun action _state =>
      switch action {
      | Loaded data => ReasonReact.Update {story_with_comments: Some data}
      },
    didMount: fun self => {
      Api.fetchStoryWithComments id (self.reduce loaded) |> ignore;
      ReasonReact.NoUpdate
    },
    render: fun {state} => {
      let commentList =
        switch state.story_with_comments {
        | Some story =>
          <div className="App">
            <div className="App-header"> (renderTitle story) (renderByline story) </div>
            <p className="App-intro"> <CommentList story /> </p>
          </div>
        | None =>
          <div className="App"> <div className="App-header"> (textEl "Loading...") </div> </div>
        };
      <div> commentList </div>
    }
  }
};
