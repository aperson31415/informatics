// ==UserScript==
// @name         ORAC Tag Manager
// @namespace    http://tampermonkey.net/
// @version      v3.2.0
// @description  Adds additional tags to orac problems (shows some hidden problems, adds starter tag, allows for bookmarking problems urself)
// @author       a_person31415
// @match        https://orac2.info/hub/personal/
// @match        https://orac2.info/problem/*
// @icon         https://www.google.com/s2/favicons?sz=64&domain=orac2.info
// @grant        GM_setValue
// @grant        GM_getValue
// ==/UserScript==

(function() {
    'use strict';

    function tag_element(content) {
        let elem = document.createElement("span");
        elem.classList.add("badge"); elem.classList.add("badge-tag");
        elem.innerText = content;
        return elem;
    }

    if(window.location.href.includes("problem")) {
        function new_tag() {
            let tag_name = prompt("Name of tag to add to problem");
            if (tag_name == '' || tag_name == undefined || tag_name == null) {alert("Okay, cancelled"); return;}
            let tag_content = GM_getValue("tags", {});
            let rev_tagcontent = GM_getValue("rev_tags", {});

            if (Object.keys(tag_content).includes(tag_name)) {
                tag_content[tag_name].push(window.location.href);
                alert("Okay, this problem has been added to the tag '" + tag_name + "'.");
            } else {
                let create_newtag = confirm("The tag '" + tag_name + "' does not exist yet. \n Would you like to create a new tag, and add this problem to it?");
                if(create_newtag) {
                    tag_content[tag_name] = [window.location.href];
                    alert("Okay, this problem has been added to the new tag '" + tag_name + "'.");
                } else {
                    alert("Okay, cancelled");
                    return;
                }
            }
            if (Object.keys(rev_tagcontent).includes(window.location.href)) {
                rev_tagcontent[window.location.href].push(tag_name);
            } else {
                rev_tagcontent[window.location.href] = [tag_name];
            }

            let problem_names = GM_getValue("problem_names", {});
            problem_names[window.location.href] = document.querySelector("h1.mb-0").innerText;
            GM_setValue("problem_names", problem_names);

            GM_setValue("tags", tag_content);
            GM_setValue("rev_tags", rev_tagcontent);
        }

        function del_tag() {
            let tag_name = prompt("Name of tag to delete from problem");
            if (tag_name == '' || tag_name == undefined || tag_name == null) {alert("Okay, cancelled"); return;}
            let tag_content = GM_getValue("tags", {});
            let rev_tagcontent = GM_getValue("rev_tags", {});

            if (Object.keys(tag_content).includes(tag_name)) {
                if(tag_content[tag_name].includes(window.location.href)) {
                    tag_content[tag_name] = tag_content[tag_name].filter(loc => loc != window.location.href);
                    alert("Okay, this problem has been removed from the tag '" + tag_name + "'.");
                    if(tag_content[tag_name] == []) {
                        let deltag = confirm("Would you like to delete the tag '" + tag_name + "'? (There are no more problems with this tag)");
                        if(deltag) {
                            delete tag_content[tag_name];
                            alert("Okay, tag '" + tag_name + "' deleted.");
                        }
                    }
                } else {
                    alert("This problem does not have the tag '" + tag_name + "'."); return;
                }
            } else {
                alert("The tag '" + tag_name + "' does not exist."); return;
            }

            rev_tagcontent[window.location.href] = rev_tagcontent[window.location.href].filter(tag => tag != tag_name);
            if (rev_tagcontent[window.location.href] == []) {
                delete rev_tagcontent[window.location.href];
            }

            GM_setValue("tags", tag_content);
            GM_setValue("rev_tags", rev_tagcontent);
        }

        function loadtags() {
            let curr_tags = GM_getValue("rev_tags", {});
            if (curr_tags == {}) return;
            if (Object.keys(curr_tags).includes(window.location.href)) {
                for(let i = 0; i < curr_tags[window.location.href].length; i++) {
                    bookmark_section.appendChild(tag_element(curr_tags[window.location.href][i]));
                }
            }
        }

        let bookmark_row = document.createElement("tr");
        let bookmark_col = document.createElement("td");
        let bookmark_section = document.createElement("div");
        bookmark_section.innerHTML = "<br>Custom Tags: ";
        loadtags();

        let plus_tag = tag_element("+");
        plus_tag.addEventListener("click", () => {new_tag();});
        let minus_tag = tag_element("-");
        minus_tag.addEventListener("click", () => {del_tag();});

        bookmark_section.appendChild(plus_tag);
        bookmark_section.appendChild(minus_tag);
        bookmark_col.appendChild(bookmark_section);
        bookmark_row.appendChild(bookmark_col);
        document.getElementsByClassName("mb-3")[0].children[0].appendChild(bookmark_row);
    }

    if (window.location.href.includes("personal")) {

        function reorder_tags(tags) {
            let tag_cont = document.getElementsByClassName("tags-container");
            tag_cont.innerHTML = `<span class="tags-description">Tags:</span>`;
            for(let i = 0; i < tags.length; i++) {
                var curr_tag = tag_element(tags[i]);
                curr_tag.setAttribute("onclick", "toggleSetTagSelected(this);");
                tag_cont.appendChild(curr_tag);
            }
        } // Later use, probably not cuz pretty much everyone has different tags unlocked

        // Custom Tags
        const btn_addtag = document.createElement("span");
        btn_addtag.innerHTML = "custom-tags";
        btn_addtag.classList.add("badge"); btn_addtag.classList.add("badge-tag");
        btn_addtag.setAttribute("onclick", "toggleSetTagSelected(this);");
        btn_addtag.addEventListener("click", function () {});

        document.getElementsByClassName("tags-container")[0].appendChild(btn_addtag);

        // Add starter problems to their own tag
        const starter_sets = ["#problem-set-starter", "#problem-set-starterset1", "#problem-set-starterset1challenge", "#problem-set-starterset2", "#problem-set-starterset2challenge", "#problem-set-starterset3", "#problem-set-starterset3challenge", "#problem-set-hub_intro_aio"];
        for(let i = 0; i < starter_sets.length; i++) {
            let selector = '[data-target="'+starter_sets[i]+'"]';
            document.querySelector(selector).parentElement.classList.add("set-tag-starter");
        }
        add_tags(["starter"]);

        // Hidden Problems
        let data = {
            "tags": [
                "cpp-practice"
            ],
            "sets": [
                {
                    "tag":"training",
                    "set_name":"Implementation Problems",
                    "set_id":"implementation-problems",
                    "problems": [
                        {
                            "problem_name":"Bernard's Magic Needles",
                            "problem_link":"https://orac2.info/problem/1106/"
                        },
                        {
                            "problem_name":"A Not So Simple Sort",
                            "problem_link":"https://orac2.info/problem/1105/"
                        },
                        {
                            "problem_name":"Pie a la Mode",
                            "problem_link":"https://orac2.info/problem/1111/"
                        },
                        {
                            "problem_name":"Stacks",
                            "problem_link":"https://orac2.info/problem/745/"
                        },
                        {
                            "problem_name":"Queues",
                            "problem_link":"https://orac2.info/problem/752/"
                        },
                        {
                            "problem_name":"Bracket Matching",
                            "problem_link":"https://orac2.info/problem/1107/"
                        },
                        {
                            "problem_name":"Twin Primes",
                            "problem_link":"https://orac2.info/problem/872/"
                        },
                        {
                            "problem_name":"Pairs",
                            "problem_link":"https://orac2.info/problem/947/"
                        }
                    ]
                },
                {
                    "tag":"training",
                    "set_name":"Graph Problems",
                    "set_id":"graph-problems",
                    "problems": [
                        {
                            "problem_name":"Quicksort",
                            "problem_link":"https://orac2.info/problem/659/"
                        },
                        {
                            "problem_name":"Gossip Chains",
                            "problem_link":"https://orac2.info/problem/738/"
                        },
                        {
                            "problem_name":"King Arthur",
                            "problem_link":"https://orac2.info/problem/978/"
                        }
                    ]
                },
                {
                    "tag":"training",
                    "set_name":"Bitmask Problems",
                    "set_id":"bitmask-problems",
                    "problems": [
                        {
                            "problem_name":"Tiling",
                            "problem_link":"https://orac2.info/problem/935/"
                        },
                        {
                            "problem_name":"Odd Jobs",
                            "problem_link":"https://orac2.info/problem/951/"
                        },
                        {
                            "problem_name":"King Arthur",
                            "problem_link":"https://orac2.info/problem/978/"
                        }
                    ]
                },
                {
                    "tag":"cpp-practice",
                    "set_name":"C++ Starter Problems",
                    "set_id":"cpp-starter",
                    "problems": [
                        {
                            "problem_name":"Addition (C++ Only)",
                            "problem_link":"https://orac2.info/problem/1309/"
                        },
                        {
                            "problem_name":"Counting to Infinity (C++ Only)",
                            "problem_link":"https://orac2.info/problem/1307/"
                        },
                        {
                            "problem_name":"Triple Hunting (C++ Only)",
                            "problem_link":"https://orac2.info/problem/1306/"
                        },
                        {
                            "problem_name":"Sitting or Standing (C++ Only)",
                            "problem_link":"https://orac2.info/problem/1308/"
                        },
                        {
                            "problem_name":"A Dish Best Served Cold (C++ Only)",
                            "problem_link":"https://orac2.info/problem/1310/"
                        }
                    ]
                }
            ]
        }
        
        let custom_tagdata = GM_getValue("tags", {});
        let problem_names = GM_getValue("problem_names", {});
        for(let i = 0; i < Object.keys(custom_tagdata).length; i++) {
            // For each tag
            var curr_tagdata = {
                tag: "custom-tags",
                set_name: "Custom Tag: " + Object.keys(custom_tagdata)[i],
                set_id: "custom-tag-" + Object.keys(custom_tagdata)[i],
                problems: []
            };
            for(let j = 0; j < Object.keys(custom_tagdata)[i].length; j++) {
                if(custom_tagdata[Object.keys(custom_tagdata)[i]][j] == undefined) {
                    continue;
                }
                curr_tagdata.problems.push({"problem_name":problem_names[custom_tagdata[Object.keys(custom_tagdata)[i]][j]], "problem_link":custom_tagdata[Object.keys(custom_tagdata)[i]][j]});
            }

            data.sets.push(curr_tagdata);
        }


        // Fetching

        async function get_text_html(url) {
            const response = await fetch(url);
            if(!response.ok) {
                throw new Error(`HTTP error! Status: ${response.status}`);
            }

            return await response.text();
        }

        async function get_html(url) {
            const htmlString = await get_text_html(url);
            const parser = new DOMParser();
            const doc = parser.parseFromString(htmlString, 'text/html');
            return doc;
        }

        async function get_badge(url) {
            const doc = await get_html(url);
            const badge = doc.getElementsByClassName("badge hub-badge")[0];
            if(badge) {
                return badge.cloneNode(true);
            } else {
                const newNode = document.createElement("span");
                newNode.innerText = "Problem does not exist";
                return newNode;
            }
        }

        async function load_from_data() {
            add_tags(data.tags);

            for (let i = 0; i < data.sets.length; i++) {
                const set = data.sets[i];
                add_set(set.set_name, set.set_id, set.tag);

                for (let j = 0; j < set.problems.length; j++) {
                    let parentNode = document.getElementById("custom-set-table-" + set.set_id);
                    let newNode = document.createElement("tr");
                    newNode.innerHTML = `
                        <td scope="row"><a href="${set.problems[j].problem_link}">${set.problems[j].problem_name}</a></td>
                        <td class="progress-column">
                            <span class="badge badge-secondary problem-placeholder">Waiting...</span>
                        </td>`;
                    parentNode.appendChild(newNode);
                }
            }

            for (let i = 0; i < data.sets.length; i++) {
                const set = data.sets[i];
                const rows = document.getElementById("custom-set-table-" + set.set_id).children;

                for (let j = 0; j < set.problems.length; j++) {
                    const badgeNode = await get_badge(set.problems[j].problem_link);
                    const scoreStuff = rows[j].children[1];
                    scoreStuff.innerHTML = "";
                    scoreStuff.appendChild(badgeNode);
                }

                const [score_obtained, max_score_possible] = add_scoring(set.set_id);
                const setElem = document.getElementById("custom_set-" + set.set_id);
                const score_elem = setElem.querySelector('.score-display');

                score_elem.innerText = `${score_obtained} / ${max_score_possible}`;
                score_elem.className = 'badge mr-auto';

                if (score_obtained === 0) {
                    score_elem.classList.add("badge-cmsred");
                } else if (score_obtained === max_score_possible) {
                    score_elem.classList.add("badge-cmsgreen");
                    setElem.classList.add("solved-set");
                } else {
                    score_elem.classList.add("badge-cmsyellow");
                }
            }
        }

        // Tags
        function add_tags(tag_names) {
            const tags_cont = document.getElementsByClassName("tags-container")[0];
            for(let i = 0; i < tag_names.length; i++) {
                const newNode = document.createElement("span");
                newNode.classList.add("badge");
                newNode.classList.add("badge-tag");
                newNode.setAttribute("onclick", "toggleSetTagSelected(this);");
                newNode.innerText = tag_names[i];
                tags_cont.appendChild(newNode);
            }
        }

        function add_set(set_name, set_id, tag_name) {
            let parentNode = document.getElementById("show-sets");
            let newNode = document.createElement("div");
            newNode.id = "custom_set-" + set_id;
            newNode.className = `problemset-display set-table set-tag-${tag_name}`;
            newNode.innerHTML = `
                <table class="table table-sm mt-0 mb-0 pointer" data-toggle="collapse" data-target="#problem-set-${set_id}">
                    <thead class="thead-dark">
                        <tr>
                            <th scope="col"><span class="set-title mr-auto">${set_name}</span></th>
                            <th scope="col" class="progress-column">
                                <div class="d-flex align-items-center">
                                    <span class="badge badge-secondary mr-auto score-display">Waiting for scores...</span>
                                    <span class="fas fa-lg fa-tag"></span>
                                </div>
                            </th>
                        </tr>
                    </thead>
                </table>`;

            let problems_table = document.createElement("div");
            problems_table.id = "problem-set-" + set_id;
            problems_table.className = "collapse show set-problems";
            
            let table_official = document.createElement("table");
            table_official.className = "table table-sm mt-0 mb-0";
            let tbody_thing = document.createElement("tbody");
            tbody_thing.id = "custom-set-table-" + set_id;
            
            table_official.appendChild(tbody_thing);
            problems_table.appendChild(table_official);
            newNode.appendChild(problems_table);
            parentNode.appendChild(newNode);
        }

        async function append_set(set_id, prob_name, link) {
            let parentNode = document.getElementById("custom-set-table-" + set_id);
            let newNode = document.createElement("tr");
            
            let nameStuff = document.createElement("td"); 
            nameStuff.setAttribute("scope", "row");
            let linkNode = document.createElement("a");
            linkNode.setAttribute("href", link);
            linkNode.innerText = prob_name;
            nameStuff.appendChild(linkNode);
            
            let scoreStuff = document.createElement("td"); 
            scoreStuff.classList.add("progress-column");
            
            let waitingNode = document.createElement("span");
            waitingNode.className = "badge badge-secondary";
            waitingNode.innerText = "Waiting for score...";
            scoreStuff.appendChild(waitingNode);
            
            newNode.appendChild(nameStuff);
            newNode.appendChild(scoreStuff);
            parentNode.appendChild(newNode);

            let badgeNode = await get_badge(link);
            scoreStuff.replaceChild(badgeNode, waitingNode);
        }

        function add_scoring(set_id) {
            const parent = document.getElementById("custom-set-table-"+set_id);
            let total_score = 0;
            let max_score = 0;
            for(let i = 0; i < parent.children.length; i++) {
                total_score += parseInt(parent.children[i].children[1].children[0].innerText);
                if(parseInt(parent.children[i].children[1].children[0].innerText) == 100) {
                    // Full solve, add tag
                    parent.children[i].className = "solved-problem";
                }
                max_score += 100;
            }
            return [total_score, max_score];
        }

        load_from_data();
    }

})();
