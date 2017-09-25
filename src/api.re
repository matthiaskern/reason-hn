let apiBaseUrl = "https://serverless-api.hackernewsmobile.com/";

let topStoriesUrl page => apiBaseUrl ^ "topstories-25-" ^ string_of_int page ^ ".json";

let storyUrl id => apiBaseUrl ^ "stories/" ^ string_of_int id ^ ".json";

type story = {
  by: string,
  descendants: int,
  id: int,
  score: int,
  time: int,
  title: string,
  url: option string
};

type stories = array story;

let parseStory json :story =>
  Json.Decode.{
    by: json |> field "by" string,
    descendants: json |> field "descendants" int,
    id: json |> field "id" int,
    score: json |> field "score" int,
    time: json |> field "time" int,
    title: json |> field "title" string,
    url: json |> optional (field "url" string)
  };

let parseStories json :array story => Json.Decode.(json |> array parseStory);

let fetchTopStories page callback =>
  Js.Promise.(
    Bs_fetch.fetch (topStoriesUrl page) |> then_ Bs_fetch.Response.text |>
    then_ (
      fun text =>
        Js.Json.parseExn text |> parseStories |> (
          fun stories => {
            callback (page, stories);
            resolve None
          }
        )
    )
  );
