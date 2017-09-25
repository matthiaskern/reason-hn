external register_service_worker : unit => unit = "default" [@@bs.module "./registerServiceWorker"];

let textEl str => ReasonReact.stringToElement str;

let intEl int => ReasonReact.stringToElement (string_of_int int);


external currentTime : unit => int = "Date.now" [@@bs.val];

/* format a timestamp in seconds as relative humanised time sentence */
let fromNow unixtime => {
  let delta = currentTime () / 1000 - unixtime;
  if (delta < 3600) {
    string_of_int (delta / 60) ^ " minutes ago"
  } else if (delta < 86400) {
    string_of_int (delta / 3600) ^ " hours ago"
  } else {
    string_of_int (delta / 86400) ^ " days ago"
  }
};

external internal_getAttribute : Js.t 'a => string => Js.null string = "getAttribute" [@@bs.send];

let getAttribute node name => Js.Null.to_opt (internal_getAttribute node name);
