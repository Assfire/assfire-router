pipeline {
    agent {
        docker { image 'alpine:latest' }
    }
    stages {
        stage('Build'){
            steps {
                sh 'echo Building...';
                sh 'echo "Artifact" > artifact.art'
            }
        }
        stage('Test') {
            steps {
                sh 'echo Testing...';
                sh 'cat artifact.art';
            }
        }
    }
}