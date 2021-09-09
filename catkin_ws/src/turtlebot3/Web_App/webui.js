// Variables :
var twist;
var cmdVel;
var publishImmidiately = true;
var PC_IP;
var manager;
var save_msg;
var save_battery
var teleop;

//PC_IP = "192.168.43.12";
//NIRYO_IP = "192.168.43.100";
PC_IP = "192.168.1.122";
NIRYO_IP = "192.168.1.130";

var ros = new ROSLIB.Ros({
    url: "ws://" + PC_IP + ":9090"
});

//----------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------

// On commence par bloquer l'affichage de la partie caméra+joystick
document.getElementById('affichage_joystick').style.display = 'block' ? 'none' : 'block';
document.getElementById('main_niryo').style.display = 'block' ? 'none' : 'block';
document.getElementById('main_meuble').style.display = 'block' ? 'none' : 'block';
document.getElementById('bandeau_joystick').style.display = 'block' ? 'none' : 'block';

// fonction qui va servir pour la publication de la vitesse des roues lors de l'usage du joystick
function moveAction(linear, angular) {
    if (linear !== undefined && angular !== undefined) {
        twist.linear.x = linear;
        twist.angular.z = angular;
    } else {
        twist.linear.x = 0;
        twist.angular.z = 0;
    }
    cmdVel.publish(twist);
}
// On initialise la variable listener qui va aller lire ce que le topic /messages publie
var listener = new ROSLIB.Topic({
    ros: ros,
    name: '/messages',
    messageType: 'std_msgs/String'
});

var listener_niryo = new ROSLIB.Topic({
    ros: ros,
    name: '/messages_niryo',
    messageType: 'std_msgs/String'
});

// lecture puis affichage du message sur l'écran de l'utilisateur
listener.subscribe(function (message) {
    //console.log('Received message on ' + listener.name + ': ' + message.data);
    save_msg = message.data;
    //console.log('message is : ' + save_msg);
    document.getElementById("Message").innerHTML = save_msg;
});

// lecture puis affichage du message sur l'écran de l'utilisateur
listener_niryo.subscribe(function (message_niryo) {
    //console.log('Received message on ' + listener.name + ': ' + message.data);
    save_msg_niryo = message_niryo.data;
    //console.log('message is : ' + save_msg);
    document.getElementById("Message_niryo").innerHTML = save_msg_niryo;
});

// initialisation de talker qui va publier dans le topic /choix les comandes envoyée par l'utilisateur codés avec un entier
var talker = new ROSLIB.Topic({
    ros: ros,
    name: '/choix',
    messageType: 'std_msgs/Int32'
});
// initialisation à -1 (car commande non valide)
var my_message = new ROSLIB.Message({
    data: -1
});

//----------------------------------------------------------------------------------------------------------------------------------------
// GESTION DES BOUTONS
//----------------------------------------------------------------------------------------------------------------------------------------


// TURTLEBOT
//----------------------------------------------------------------------------------------------------------------------------------------

// Bouton salon : qui publie la valeur 1 sur le topic /choix afin d'avertir le robot qu'il doit aller au salon
function Salon() {
    document.getElementById("salon-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/salon.wav');
    music.play();
    my_message.data = 1;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Chambre() {
    document.getElementById("chambre-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/chambre.wav');
    music.play();
    my_message.data = 2;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Dock() {
    document.getElementById("base-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/dock.wav');
    music.play();
    my_message.data = 3;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Plan() {
    document.getElementById("plan-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/cuisine_plan.wav');
    music.play();
    my_message.data = 4;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Table() {
    document.getElementById("table-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/cuisine_table.wav');
    music.play();
    my_message.data = 5;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Frigidaire() {
    document.getElementById("frigidaire-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/cuisine_frigidaire.wav');
    music.play();
    my_message.data = 6;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Stop() {
    document.getElementById("stop-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/stop.wav');
    music.play();
    my_message.data = 7;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Urgence() {
    document.getElementById("urgence-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/urgence.wav');
    music.play();
    my_message.data = 8;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Reactivation() {
    document.getElementById("reactivation-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/reactivation.wav');
    music.play();
    my_message.data = 9;
    talker.publish(my_message);
    console.log(my_message.data);
}

// NIRYO ONE
//----------------------------------------------------------------------------------------------------------------------------------------

function Servir() {
    document.getElementById("servir-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/servir.wav');
    music.play();
    my_message.data = 10;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Pause_bras() {
    document.getElementById("pause-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/pause.wav');
    music.play();
    my_message.data = 11;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Reprise_bras() {
    document.getElementById("reprise-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/reprise.wav');
    music.play();
    my_message.data = 12;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Ranger() {
    document.getElementById("ranger-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/ranger.wav');
    music.play();
    my_message.data = 13;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Arret_action() {
    document.getElementById("arret-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/arret_niryo.wav');
    music.play();
    my_message.data = 14;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Observation() {
    document.getElementById("observation-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/observation.wav');
    music.play();
    my_message.data = 15;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Center() {
    document.getElementById("center-img");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/pos_init.wav');
    music.play();
    my_message.data = 99;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Up() {
    document.getElementById("up-img");
    my_message.data = 100;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Left() {
    document.getElementById("left-img");
    my_message.data = 101;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Right() {
    document.getElementById("right-img");
    my_message.data = 102;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Down() {
    document.getElementById("down-img");
    my_message.data = 103;
    talker.publish(my_message);
    console.log(my_message.data);
}

// MEUBLE INTELLIGENT
//----------------------------------------------------------------------------------------------------------------------------------------

function Pause_meuble() {
    document.getElementById("arret_meuble-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/pause.wav');
    music.play();
    my_message.data = 16;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Reprise_meuble() {
    document.getElementById("marche_meuble-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/reprise.wav');
    music.play();
    my_message.data = 17;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Avancer() {
    document.getElementById("avancer-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/avancer.wav');
    music.play();
    my_message.data = 18;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Reculer() {
    document.getElementById("reculer-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/reculer.wav');
    music.play();
    my_message.data = 19;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Sortir() {
    document.getElementById("sortir-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/sortir.wav');
    music.play();
    my_message.data = 20;
    talker.publish(my_message);
    console.log(my_message.data);
}


function Rentrer() {
    document.getElementById("rentrer-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/rentrer.wav');
    music.play();
    my_message.data = 20;
    talker.publish(my_message);
    console.log(my_message.data);
}


function Arret_meuble_action() {
    document.getElementById("arret_meuble-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/arret_meuble.wav');
    music.play();
    my_message.data = 21;
    talker.publish(my_message);
    console.log(my_message.data);
}

function Monter() {
    document.getElementById("monter-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/monter.wav');
    music.play();
    my_message.data = 20;
    talker.publish(my_message);
    console.log(my_message.data);
}


function Descendre() {
    document.getElementById("descendre-btn");
    var music = new Audio('https://raw.githubusercontent.com/Anton1B/Base_mobile_MaD/main/src_web/sounds/descendre.wav');
    music.play();
    my_message.data = 21;
    talker.publish(my_message);
    console.log(my_message.data);
}

//----------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------

// fonction qui va publier dans /cmd_vel pour donenr des vitesses linéaire et angulaires 
function initVelocityPublisher() {
    // Init message with zero values.
    twist = new ROSLIB.Message({
        linear: {
            x: 0,
            y: 0,
            z: 0
        },
        angular: {
            x: 0,
            y: 0,
            z: 0
        }
    });
    // Init topic object
    cmdVel = new ROSLIB.Topic({
        ros: ros,
        name: '/cmd_vel',
        messageType: 'geometry_msgs/Twist'
    });
    // Register publisher within ROS system
    cmdVel.advertise();
}

window.onload = function () {

    // // Init handle for rosbridge_websocket
    ros = new ROSLIB.Ros({
        url: "ws://" + PC_IP + ":9090"
    });

    initVelocityPublisher();

    // get handle for video placeholder
    video = document.getElementById('video');

    // taille de la fenêtre de la caméra
    video.height = 308;
    video.width = 410;
    video.margin = 1;
    //video.height = 480;
    //video.width = 640;
    //video.margin = 100;

    // Source de la caméra
    video.src = "http://" + PC_IP + ":8080/stream?topic=/raspicam_node/image&type=mjpeg&quality=50";

    video.onload = function () {
        // joystick and keyboard controls will be available only when video is correctly loaded
        //createJoystick();
        //initTeleopKeyboard();
    };

   //VIDEO NIRYO 
    video3 = document.getElementById('video_niryo');
    video3.height = 308;
    video3.width = 410;
    video3.margin = 1;

    //Source de la caméra
    //video3.src = "http://" + PC_IP + ":8080/stream?topic=/niryo_one_vision/compressed_video_stream/compressed&type=ros_compressed";
    video3.src = "http://" + PC_IP + ":8080/stream?topic=/niryo_one_vision/video_stream&type=mjpeg&quality=50";
    video3.onload = function () {};

}


/*
function initTeleopKeyboard() {
    // Use w, s, a, d keys to drive your robot

    // Check if keyboard controller was aready created
    if (teleop == null) {
        // Initialize the teleop.
        teleop = new KEYBOARDTELEOP.Teleop({
            ros: ros,
            topic: '/cmd_vel'
        });
    }
}
*/

// Récupération du niveau de batterie :
var battery = new ROSLIB.Topic({
    ros: ros,
    name: '/battery_level',
    messageType: 'std_msgs/Int32'
});

battery.subscribe(function (level) {
    // Affichage et mise à jour de la barre de batterie :
    battery_status.style = "width:" + level.data + "%" + ";background-color:#62cdff";
    battery_status.innerHTML = level.data + '%';
});


//----------------------------------------------------------------------------------------------------------------------------------------
// AFFICHAGE
//----------------------------------------------------------------------------------------------------------------------------------------

// On affiche tout sauf le joystick et l'info liée au joystick + le bouton :
function Affichage_menu() {
    document.getElementById("menu_principal");
    // Affichage :
    // main1 correspond au pourcentage de batterie et main2 correspond aux infos+boutons.
    // La caméra se trouve entre les deux
    document.getElementById('bandeau').style.display = 'none' ? 'block' : 'none';
    document.getElementById('main1').style.display = 'none' ? 'block' : 'none';
    document.getElementById('affichage_video').style.display = 'none' ? 'block' : 'none';
    document.getElementById('main2').style.display = 'none' ? 'block' : 'none';
    // Bloquage
    // cam correspond au joystick+bouton+info la caméra se trouve avant
    document.getElementById('affichage_joystick').style.display = 'block' ? 'none' : 'block';
    document.getElementById('main_niryo').style.display = 'block' ? 'none' : 'block';
    document.getElementById('main_meuble').style.display = 'block' ? 'none' : 'block';
    document.getElementById('bandeau_joystick').style.display = 'block' ? 'none' : 'block';
}

function Affichage_menu_niryo() {
    document.getElementById("menu_niryo");
    // Affichage :
    document.getElementById('main_niryo').style.display = 'none' ? 'block' : 'none';
    // Bloquage
    document.getElementById('main1').style.display = 'block' ? 'none' : 'block';
    document.getElementById('main2').style.display = 'block' ? 'none' : 'block';
    document.getElementById('affichage_joystick').style.display = 'block' ? 'none' : 'block';
    document.getElementById('affichage_video').style.display = 'block' ? 'none' : 'block';
    document.getElementById('bandeau').style.display = 'block' ? 'none' : 'block';
}

function Affichage_menu_meuble() {
    document.getElementById("menu_meuble");
    // Affichage :
    document.getElementById('main_meuble').style.display = 'none' ? 'block' : 'none';
    // Bloquage
    document.getElementById('main1').style.display = 'block' ? 'none' : 'block';
    document.getElementById('main2').style.display = 'block' ? 'none' : 'block';
    document.getElementById('affichage_joystick').style.display = 'block' ? 'none' : 'block';
    document.getElementById('affichage_video').style.display = 'block' ? 'none' : 'block';
    document.getElementById('bandeau').style.display = 'block' ? 'none' : 'block';


}


// Affichage de menu avec caméra + joystick
function Affichage_cam() {
    // On affiche la partie camera et joystick et on bloque le reste :
    document.getElementById("camera_joystick");
    document.getElementById("bandeau_joystick").style.display = 'none' ? 'block' : 'none';
    document.getElementById('affichage_video').style.display = 'none' ? 'block' : 'none';
    document.getElementById('affichage_joystick').style.display = 'none' ? 'block' : 'none';

    document.getElementById('main1').style.display = 'block' ? 'none' : 'block';
    document.getElementById('main2').style.display = 'block' ? 'none' : 'block';
    document.getElementById('main_niryo').style.display = 'block' ? 'none' : 'block';
    document.getElementById('bandeau').style.display = 'block' ? 'none' : 'block';


    // Création du joystick
    function createJoystick() {
        // Check if joystick was aready created and if there is enough battery
        if (manager == null) {
            joystickContainer = document.getElementById('joystick');
            // joystck configuration, if you want to adjust joystick, refer to:
            // https://yoannmoinet.github.io/nipplejs/
            var options = {
                zone: joystickContainer,
                position: { left: 50 + '%', top: 60 + 'px' },
                mode: 'static',
                size: 100,
                color: '#0066ff',
                restJoystick: true,
            };

            manager = nipplejs.create(options);
            // event listener for joystick move
            manager.on('move', function (evt, nipple) {
                fadeTime: 0;
                // nipplejs returns direction is screen coordiantes
                // we need to rotate it, that dragging towards screen top will move robot forward
                var direction = nipple.angle.degree - 90;
                if (direction > 180) {
                    direction = -(450 - nipple.angle.degree);
                }
                // convert angles to radians and scale linear and angular speed
                // adjust if youwant robot to drvie faster or slower
                var lin = Math.cos(direction / 57.29) * nipple.distance * 0.005;
                var ang = Math.sin(direction / 57.29) * nipple.distance * 0.05;
                // nipplejs is triggering events when joystic moves each pixel
                // we need delay between consecutive messege publications to 
                // prevent system from being flooded by messages
                // events triggered earlier than 50ms after last publication will be dropped 
                if (publishImmidiately) {
                    publishImmidiately = false;
                    moveAction(lin, ang);
                    setTimeout(function () {
                        publishImmidiately = true;
                    }, 50);
                }
            });
            // event litener for joystick release, always send stop message
            manager.on('end', function () {
                moveAction(0, 0);
            });
        }
    }
    createJoystick();
}



