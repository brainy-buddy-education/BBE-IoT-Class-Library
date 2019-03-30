console.log('Loading function');

const doc = require('dynamodb-doc');

const dynamo = new doc.DynamoDB();


/**
 * Demonstrates a simple HTTP endpoint using API Gateway. You have full
 * access to the request and response payload, including headers and
 * status code.
 *
 * To scan a DynamoDB table, make a GET request with the TableName as a
 * query string parameter. To put, update, or delete an item, make a POST,
 * PUT, or DELETE request respectively, passing in the payload to the
 * DynamoDB API as a JSON body.
 */
exports.handler = (event, context, callback) => {
    //console.log('Received event:', JSON.stringify(event, null, 2));

    const done = (err, res) => callback(null, {
        statusCode: err ? '400' : '200',
        body: err ? err.message : JSON.stringify(res),
        headers: {
            'Content-Type': 'application/json',
        },
    });
    //var serialnumber = event['params']['querystring']['sn']; //this one is also OK.
    var serialnumber = event.params.querystring.sn;

    switch (event.context['http-method']) {
        case 'GET':
            //dynamo.scan({ TableName: event.queryStringParameters.TableName }, done);
            switch (serialnumber){
                case '12345678':
                    done(0, 'good serial number');
                    break;
                default:
                    done(0, 'bad');
            }
            //done(0, event);
            break;
        default:
            done(new Error(`Unsupported method "${event.httpMethod}"`));
    }
};
