type state = {
  stories: Api.stories,
  page: int,
  loading: bool
};

type action =
  | Loaded (int, Api.stories)
  | Loading;

let component = ReasonReact.reducerComponent "FrontPage";

let make _children => {
  let fetchPage {ReasonReact.state: state, reduce} => {
    Api.fetchTopStories state.page (reduce (fun payload => Loaded payload)) |> ignore;
    reduce (fun () => Loading) ()
  };
  {
    ...component,
    initialState: fun () => ({stories: [||], page: 0, loading: false}: state),
    didMount: fun self => {
      fetchPage self;
      ReasonReact.NoUpdate
    },
    reducer: fun action state =>
      switch action {
      | Loading => ReasonReact.Update {...state, loading: true}
      | Loaded (page, data) => ReasonReact.Update {stories: data, page: page + 1, loading: false}
      },
    render: fun self => {
      let stories =
        if (Array.length self.state.stories > 0) {
          Array.mapi
            (fun index story => <ListItem key=(string_of_int index) index story />)
            self.state.stories
        } else {
          [||]
        };
      <div className="App">
        <div className="App-header"> <h2> (ReasonReact.stringToElement "Reason HN") </h2> </div>
        <div className="App-main"> (ReasonReact.arrayToElement stories) </div>
      </div>
    }
  }
};
