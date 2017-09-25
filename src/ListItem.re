open Utils;

[%bs.raw {|require('./ListItem.css')|}];

let component = ReasonReact.statelessComponent "ListItem";

let make story::(story:Api.story) index::(index: int) _children => {
  let renderTitle () => {
    let content =
      <div className="ListItem_storyTitle">
        (intEl (index + 1))
        (textEl ". ")
        <span className="ListItem_storyTitleText"> (textEl story.title) </span>
      </div>;
    let link =
      switch story.url {
      | Some url => <a href=url className="ListItem_link"> content </a>
      | None =>
        <a href=("#/comments/" ^ string_of_int story.id) className="ListItem_link">
          content
        </a>
      };
    <div> link </div>
  };

 let renderByLine () =>
  <div className="ListItem_row ListItem_byline">
      <span className="ListItem_number"> (intEl story.score) </span>
      (textEl " points")
      <span>
        <span className="ListItem_storyTime">
          (textEl (" submitted " ^ fromNow story.time ^ " by " ^ story.by))
        </span>
      </span>
    </div>;

  let renderArticleButton () =>
    <div className="ListItem_flexRow">
      <div className="ListItem_storyCell">
        (renderTitle ())
        (renderByLine ())
      </div>
    </div>;

  let renderCommentsButton () =>
    <div className="ListItem_commentsCell">
      <a href=("#/comments/" ^ string_of_int story.id) className="ListItem_link">
        <div>
          <span className="ListItem_commentsText">
            <span className="ListItem_number"> (intEl story.descendants) </span>
            <br />
            (textEl " comments")
          </span>
        </div>
      </a>
    </div>;

    {
      ...component,
      render: fun _self => {
        <div className="ListItem_itemRow">
          (renderArticleButton ())
          (renderCommentsButton ())
        </div>
      },
    };
};
